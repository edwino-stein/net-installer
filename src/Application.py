
class Application(object):
    
    app = None
    viewer = None

    def __init__(self, createViewHandle):
        Application.app = self
        self.viewer = createViewHandle()
    
    def init(self):
        print('init')

    def run(self):
        self.viewer.loop()
        