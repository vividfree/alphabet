# base text util
# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18
#   NOTE  : The input parameters of the functions within BaseTextUtil need to be string encoding with Unicode,
#           so you should use str.decode(...) first before invoking these functions.


class BaseTextUtil(object):

    # some has_* function()

    @staticmethod
    def has_alphabet(ustring):
        for uchar in ustring:
            if BaseTextUtil.is_alphabet(uchar):
                return True
        return False

    @staticmethod
    def has_broad_chinese(ustring):
        for uchar in ustring:
            if BaseTextUtil.is_broad_chinese(uchar):
                return True
        return False

    @staticmethod
    def has_chinese(ustring):
        for uchar in ustring:
            if BaseTextUtil.is_chinese(uchar):
                return True
        return False

    @staticmethod
    def has_number(ustring):
        for uchar in ustring:
            if BaseTextUtil.is_number(uchar):
                return True
        return False

    # some is_* function()

    @staticmethod
    def is_ip(ustring):
        items = ustring.split('.')
        if len(items) != 4:
            return False
        for item in items:
            if not item.isdigit() or int(item) > 255:
                return False
        return True

    @staticmethod
    def is_all_alpha(ustring):
        for item in ustring:
            if not BaseTextUtil.is_alphabet(item):
                return False
        return True

    @staticmethod
    def is_all_number(ustring):
        for item in ustring:
            if not BaseTextUtil.is_number(item):
                return False
        return True

    @staticmethod
    def is_all_alpha_and_number(ustring):
        for item in ustring:
            if not BaseTextUtil.is_alphabet(item) and not BaseTextUtil.is_number(item):
                return False
        return True

    @staticmethod
    def is_alphabet(uchar):
        if (u'\u0041' <= uchar <= u'\u005a') or (u'\u0061' <= uchar <= u'\u007a'):
            return True
        else:
            return False

    @staticmethod
    def is_broad_chinese(uchar):
        x = ord(uchar)
        # Punct & Radicals
        if 0x2e80 <= x <= 0x33ff:
            return True
        # Fullwidth Latin Characters
        elif 0xff00 <= x <= 0xffef:
            return True
        # CJK Unified Ideographs &
        # CJK Unified Ideographs Extension A
        elif 0x4e00 <= x <= 0x9fbb:
            return True
        # CJK Compatibility Ideographs
        elif 0xf900 <= x <= 0xfad9:
            return True
        # CJK Unified Ideographs Extension B
        elif 0x20000 <= x <= 0x2a6d6:
            return True
        # CJK Compatibility Supplement
        elif 0x2f800 <= x <= 0x2fa1d:
            return True
        else:
            return False

    @staticmethod
    def is_chinese(uchar):
        if u'\u4e00' <= uchar <= u'\u9fa5':
            return True
        else:
            return False

    @staticmethod
    def is_number(uchar):
        if u'\u0030' <= uchar <= u'\u0039':
            return True
        else:
            return False

    @staticmethod
    def is_visible_ascii(uchar):
        x = ord(uchar)
        if 0x0020 <= x <= 0x007E:
            return True
        else:
            return False

    # some fundamental function()

    @staticmethod
    def banjiao_2_quanjiao(uchar):
        inside_code = ord(uchar)
        if inside_code < 0x0020 or inside_code > 0x7e:
            return uchar
        if inside_code == 0x0020:
            inside_code = 0x3000
        else:
            inside_code += 0xfee0
        return unichr(inside_code)

    @staticmethod
    def quanjiao_2_banjiao(uchar):
        inside_code = ord(uchar)
        if inside_code == 0x3000:
            inside_code = 0x0020
        else:
            inside_code -= 0xfee0
        if inside_code < 0x0020 or inside_code > 0x7e:
            return uchar
        return unichr(inside_code)

    @staticmethod
    def string_quanjiao_2_banjiao(ustring):
        return u"".join([BaseTextUtil.quanjiao_2_banjiao(uchar) for uchar in ustring])

    @staticmethod
    def delete_sys_chars(ustring):
        _sys_uchar_table = {
            1: ord(' '),
            2: ord(' '),
            3: ord(' '),
            4: ord(' '),
            5: ord(' '),
            ord('\t'): ord(' ')
        }
        return ustring.translate(_sys_uchar_table)

    @staticmethod
    def normalize(ustring):
        return BaseTextUtil.delete_sys_chars(BaseTextUtil.string_quanjiao_2_banjiao(ustring).lower()).strip()
