#include <iostream>
#include <string>

namespace hadoop_streaming_mapreduce {

using namespace std;

// In Hadoop Stream Mapreduce, data are saved in text files, and each
// line contains a key-value pair.  In particular, each line consists
// of the following content:
//   key (as string) + kKeyValueDelimitor + value (as rest of the line)
extern const char kKeyValueDelimitor;

class Counter {
 public:
  Counter(const std::string& name): name_(name) {
  }

  void Increment(uint32_t i) {
    std::cerr << std::endl << "reporter:counter:UserDefinedCounter,"
              << name_ << "," << i <<std::endl;
  }

 private:
  std::string name_;
};

class Mapper {
 public:
  Mapper() {}
  virtual ~Mapper() {}

  virtual void Start() {}
  virtual void Map(const string& key, const string& value);
  virtual void Flush() {}

 protected:
  void Output(const string& key, const string& value);
  void OutputWithSecondaryKey(const string& key, const string& secondary_key,
                              const string& value);
};

// Iterates over the values aggregated together by the same key.  Each
// value has a corresponding secondary_key.
class ReduceInputIterator {
 public:
  enum State {
    UNINITIALIZED,
    IN_AN_INPUT,
    FINISHED_AN_INPUT,
    END_OF_SHARD
  };

  ReduceInputIterator(istream* input_stream)
      : state_(UNINITIALIZED),
        input_stream_(input_stream) {}

  void Next();
  void DiscardRemainingValues();

  bool Done() const { return state_ == FINISHED_AN_INPUT || state_ == END_OF_SHARD; }
  bool EOS() const  { return state_ == END_OF_SHARD; }

  const string& key() const;
  const string& secondary_key() const;
  const string& value() const;

 private:
  State state_;
  string key_, secondary_key_, value_;
  string next_key_;
  istream* input_stream_;

  // Fetch a tuple of key,secondary_key,value from standard input.
  // Returns false if the input operation is failed.
  bool FetchValue(string* key, string* secondary_key, string* value);
};

class Reducer {
 public:
  Reducer() {}
  virtual ~Reducer() {}

  virtual void Start() {}
  virtual void Reduce(ReduceInputIterator* reduce_inputs);
  virtual void Flush() {}

 protected:
  void Output(const string& key, const string& value);
};

void MapWorker(istream* input_stream, Mapper* mapper);
void ReduceWorker(istream* input_stream, Reducer* reducer);

int MapReduceMain(int argc, char** argv,
                  Mapper* mapper,
                  Reducer* reducer,
                  Reducer* combiner);

}  // namespace hadoop_streaming_mapreduce
