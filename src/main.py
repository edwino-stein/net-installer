import sys
from GUI import createViewer
from Application import Application

def main(argv):
    app = Application(createViewer)
    app.init()
    app.run()

if __name__ == "__main__":
    main(sys.argv)