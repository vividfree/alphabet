# project path getter
# Author: vividfree (vividfree@qq.com)
#  Date : 2017-08-18
#  NOTE : need to modify python_egg_file() in ProjectPathGetter class before using.

import os


class ProjectPathGetter(object):
    def __init__(self):
        self._root_dir = os.path.join(os.path.dirname(__file__), '../..')

    def working_root(self):
        return self._root_dir

    def bin_root(self):
        return os.path.join(self._root_dir, 'bin')

    def conf_root(self):
        return os.path.join(self._root_dir, 'conf')

    def data_root(self):
        return os.path.join(self._root_dir, 'data')

    def lib_root(self):
        return os.path.join(self._root_dir, 'lib')

    def python_root(self):
        return os.path.join(self._root_dir, 'python')

    def python_egg_file(self):
        return os.path.join(self.python_root(), 'dist', 'xxx.egg')

    def shell_root(self):
        return os.path.join(self._root_dir, 'shell')

    def src_root(self):
        return os.path.join(self._root_dir, 'src')

    def test_data_root(self):
        return os.path.join(self._root_dir, 'test_data')
