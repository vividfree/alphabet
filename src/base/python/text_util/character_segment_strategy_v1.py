# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18
#   NOTE  : The input parameters of the functions within TextUtilForQueryEmbedding
#           need to be string encoding with Unicode, so you should use str.decode(...)
#           first before invoking these functions.

from text_util.base_text_util import BaseTextUtil
from text_util.character_segment_base_class import CharacterSegmentBaseClass


class CharacterSegmentStrategyV1(CharacterSegmentBaseClass):
    SEPARATOR = u' '

    class State(object):
        START = 0,
        MIDDLE = 1

    class InputType(object):
        CHINESE = 0,
        ALPHABET = 1,
        NUMBER = 2,
        PUNCTUATION_TYPE1 = 3,
        PUNCTUATION_TYPE2 = 4,
        INVALID = 5

    @staticmethod
    def is_punctuation_type1(uchar):
        if uchar in [u'\u0025', u'\u0026', u'\u002d', u'\u002e', u'\u002f',
                     u'\u003a', u'\u003d', u'\u003f', u'\u0040']:
            # if uchar is % & - . / : = ? @
            return True
        else:
            return False

    @staticmethod
    def is_punctuation_type2(uchar):
        if BaseTextUtil.is_visible_ascii(uchar):
            if not CharacterSegmentStrategyV1.is_punctuation_type1(uchar):
                return True
        return False

    class StateMachine(object):

        def __init__(self):
            self.cur_state = CharacterSegmentStrategyV1.State.START
            self.list_cache_uchar = list()

        def run(self, uchar):
            # step 1: detect the type of uchar
            type_of_uchar = CharacterSegmentStrategyV1.InputType.INVALID
            if BaseTextUtil.is_chinese(uchar):
                type_of_uchar = CharacterSegmentStrategyV1.InputType.CHINESE
            elif BaseTextUtil.is_alphabet(uchar):
                type_of_uchar = CharacterSegmentStrategyV1.InputType.ALPHABET
            elif BaseTextUtil.is_number(uchar):
                type_of_uchar = CharacterSegmentStrategyV1.InputType.NUMBER
            elif CharacterSegmentStrategyV1.is_punctuation_type1(uchar):
                type_of_uchar = CharacterSegmentStrategyV1.InputType.PUNCTUATION_TYPE1
            elif CharacterSegmentStrategyV1.is_punctuation_type2(uchar):
                type_of_uchar = CharacterSegmentStrategyV1.InputType.PUNCTUATION_TYPE2

            # step 2: state transition
            if CharacterSegmentStrategyV1.State.START == self.cur_state:
                if CharacterSegmentStrategyV1.InputType.CHINESE == type_of_uchar:
                    return [uchar]
                elif CharacterSegmentStrategyV1.InputType.ALPHABET == type_of_uchar:
                    self.cur_state = CharacterSegmentStrategyV1.State.MIDDLE
                    self.list_cache_uchar.append(uchar)
                    return None
                elif CharacterSegmentStrategyV1.InputType.NUMBER == type_of_uchar:
                    self.cur_state = CharacterSegmentStrategyV1.State.MIDDLE
                    self.list_cache_uchar.append(uchar)
                    return None
                elif CharacterSegmentStrategyV1.InputType.PUNCTUATION_TYPE1 == type_of_uchar:
                    return None
                elif CharacterSegmentStrategyV1.InputType.PUNCTUATION_TYPE2 == type_of_uchar:
                    return None
                elif CharacterSegmentStrategyV1.InputType.INVALID == type_of_uchar:
                    return None
            elif CharacterSegmentStrategyV1.State.MIDDLE == self.cur_state:
                if CharacterSegmentStrategyV1.InputType.CHINESE == type_of_uchar:
                    self.cur_state = CharacterSegmentStrategyV1.State.START
                    last_ustring = u''.join(self.list_cache_uchar)
                    self.list_cache_uchar = list()
                    return [last_ustring, uchar]
                elif CharacterSegmentStrategyV1.InputType.ALPHABET == type_of_uchar:
                    self.list_cache_uchar.append(uchar)
                    return None
                elif CharacterSegmentStrategyV1.InputType.NUMBER == type_of_uchar:
                    self.list_cache_uchar.append(uchar)
                    return None
                elif CharacterSegmentStrategyV1.InputType.PUNCTUATION_TYPE1 == type_of_uchar:
                    self.list_cache_uchar.append(uchar)
                    return None
                elif CharacterSegmentStrategyV1.InputType.PUNCTUATION_TYPE2 == type_of_uchar:
                    self.cur_state = CharacterSegmentStrategyV1.State.START
                    last_ustring = u''.join(self.list_cache_uchar)
                    self.list_cache_uchar = list()
                    return [last_ustring]
                elif CharacterSegmentStrategyV1.InputType.INVALID == type_of_uchar:
                    self.cur_state = CharacterSegmentStrategyV1.State.START
                    last_ustring = u''.join(self.list_cache_uchar)
                    self.list_cache_uchar = list()
                    return [last_ustring]

        def reset(self):
            if CharacterSegmentStrategyV1.State.MIDDLE == self.cur_state:
                last_ustring = u''.join(self.list_cache_uchar)
                self.cur_state = CharacterSegmentStrategyV1.State.START
                self.list_cache_uchar = list()
                return [last_ustring]
            else:
                return None

    def __init__(self):
        CharacterSegmentBaseClass.__init__(self)
        self.state_machine = CharacterSegmentStrategyV1.StateMachine()

    def normalize_2_list(self, ustring):
        return_list = list()
        tmp_ustring = BaseTextUtil.normalize(ustring)
        for uchar in tmp_ustring:
            ret_val = self.state_machine.run(uchar)
            if ret_val is not None:
                return_list.extend(ret_val)
        ret_val = self.state_machine.reset()
        if ret_val is not None:
            return_list.extend(ret_val)
        return return_list

    def normalize_2_ustring(self, ustring):
        return_list = self.normalize_2_list(ustring)
        return CharacterSegmentStrategyV1.SEPARATOR.join(return_list)
