import  os

def working_root():
    return os.path.join(os.path.dirname(__file__), '../..')

def bin_root():
    return os.path.join(working_root(), 'bin')

def conf_root():
    return os.path.join(working_root(), 'conf')

def data_root():
    return os.path.join(working_root(), 'data')

def lib_root():
    return os.path.join(working_root(), 'lib')

def python_root():
    return os.path.join(working_root(), 'python')

def shell_root():
    return os.path.join(working_root(), 'shell')

def src_root():
    return os.path.join(working_root(), 'src')
