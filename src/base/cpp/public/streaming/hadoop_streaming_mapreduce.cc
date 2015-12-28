#include "streaming/hadoop_streaming_mapreduce.h"

#include <string.h>

#include <iomanip>
#include <iostream>
#include <vector>

#include "streaming/check_log.h"
//#include "streaming/string_split.h"

namespace hadoop_streaming_mapreduce {

using namespace std;

const char kKeyValueDelimitor = '\t';

//------------------------------------------------------------------------------
// Implementation of class Mapper
//------------------------------------------------------------------------------

void Mapper::Map(const string& key, const string& value) {
  Output(key, value);
}

void Mapper::Output(const string& key, const string& value) {
  if (value.empty()) {
    cout << key << endl;
    return;
  }
  cout << key << kKeyValueDelimitor << value << endl;
}

void Mapper::OutputWithSecondaryKey(const string& key,
                                    const string& secondary_key,
                                    const string& value) {
  cout << key << kKeyValueDelimitor
       << secondary_key <<  kKeyValueDelimitor
       << value << endl;
}

void MapWorker(istream* input_stream, Mapper* mapper) {
  mapper->Start();
  string line;
  while (getline(*input_stream, line)) {
//    string key, value;
//    size_t delim_pos = line.find(kKeyValueDelimitor);
//    if (delim_pos != string::npos) {
//      key = line.substr(0, delim_pos);
//      value = line.substr(delim_pos + 1);
//      mapper->Map(key, value);
//    } else {
//      // If there is no delimitor in the line, the key is considered
//      // an empty string and the value contains the whole line.
//      mapper->Map(key, line);
//    }
    string key;
    mapper->Map(key, line);
  }
  mapper->Flush();
}

//------------------------------------------------------------------------------
// Implementation of class ReduceInputIterator
//------------------------------------------------------------------------------

void ReduceInputIterator::Next() {
  if (state_ == UNINITIALIZED ) {
    if (FetchValue(&key_, &secondary_key_, &value_)) {
      state_ = IN_AN_INPUT;
    } else {
      state_ = END_OF_SHARD;
    }
  } else if (state_ == IN_AN_INPUT) {
      if (FetchValue(&next_key_, &secondary_key_, &value_)) {
        if (next_key_ != key_) {
          state_ = FINISHED_AN_INPUT;
        }
      } else {
        state_ = END_OF_SHARD;
      }
  } else if (state_ == FINISHED_AN_INPUT) {
    // We update key_ by next_key_ here but not during the transitting
    // from IN_AN_INPUT to FINISHED_AN_INPUT, so that key() can return
    // the valid key under state FINISHED_AN_INPUT or END_OF_SHARD.
    key_ = next_key_;
    state_ = IN_AN_INPUT;
  } else if (state_ == END_OF_SHARD) {
    // Nothing to do here, since there is no way to advance anymore
    // from the state END_OF_SHARD.
  } else {
    // Any unknown state is transfered to UNINITIALIZED.
    // TODO(wyi): we should CHECK(false) here.
    state_ = UNINITIALIZED;
  }
}

void ReduceInputIterator::DiscardRemainingValues() {
  while (state_ != FINISHED_AN_INPUT) {
  // while (state_ != FINISHED_AN_INPUT && state_ != END_OF_SHARD) {
    Next();
  }
}

const string& ReduceInputIterator::key() const {
  CHECK(state_ != UNINITIALIZED);
  return key_;
}

const string& ReduceInputIterator::secondary_key() const {
  CHECK(state_ != UNINITIALIZED);
  CHECK(state_ != FINISHED_AN_INPUT);
  CHECK(state_ != END_OF_SHARD);
  return secondary_key_;
}

const string& ReduceInputIterator::value() const {
  CHECK(state_ != UNINITIALIZED);
  CHECK(state_ != FINISHED_AN_INPUT);
  CHECK(state_ != END_OF_SHARD);
  return value_;
}

bool ReduceInputIterator::FetchValue(string* key,
                                     string* secondary_key,
                                     string* value) {
  string line;
  if (!getline(*input_stream_, line)) {
    return false;
  }

  size_t first_delim = line.find(kKeyValueDelimitor);
  if (first_delim == string::npos) {
    // If there is no delimitor in the line, the whole line is
    // considered a vlaue with key is an empty string.
    key->clear();
    secondary_key->clear();
    value->swap(line);
  } else {
    *key = line.substr(0, first_delim);
    size_t second_delim = line.find(kKeyValueDelimitor, first_delim + 1);
    if (second_delim == string::npos) {
      secondary_key->clear();
      *value =  line.substr(first_delim + 1);
    } else {
      *secondary_key = line.substr(first_delim + 1,
                                   second_delim - first_delim - 1);
      *value = line.substr(second_delim + 1);
    }
  }
  return true;
}

void Reducer::Reduce(ReduceInputIterator* reduce_inputs) {
  for (; !reduce_inputs->Done(); reduce_inputs->Next()) {
    Output(reduce_inputs->value(), reduce_inputs->value());
  }
}

void Reducer::Output(const string& key, const string& value) {
  if (value.empty()) {
    cout << key << endl;
    return;
  }
  cout << key << kKeyValueDelimitor << value << endl;
}

void ReduceWorker(istream* input_stream, Reducer* reducer) {
  ReduceInputIterator iterator(input_stream);
  reducer->Start();
  for (iterator.Next(); !iterator.EOS(); iterator.Next()) {
    reducer->Reduce(&iterator);
  }
  reducer->Flush();
}

int MapReduceMain(int argc, char** argv,
                  Mapper* mapper,
                  Reducer* reducer,
                  Reducer* combiner) {
  if (argc > 1) {
    if (strcmp(argv[1], "map") == 0) {
      std::cerr << "start map" << std::endl;
      MapWorker(&std::cin, mapper);
      return 0;
    } else if (strcmp(argv[1], "reduce") == 0) {
      std::cerr << "start reduce" << std::endl;
      ReduceWorker(&std::cin, reducer);
      return 0;
    } else if (strcmp(argv[1], "combine") == 0) {
      std::cerr << "start combine" << std::endl;
      ReduceWorker(&std::cin, combiner);
      return 0;
    }
  }
  return -1;
}

}  // namespace hadoop_streaming_mapreduce
