
class Application(object):
    
    app = None

    def __init__(self, createViewHandle):
        Application.app = self
    
    def init(self):
        print('init')

    def run(self):
        print('run')
        