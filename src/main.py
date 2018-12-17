import sys

from GUI import createViewer
from Application import Application

def main(argv):

    app = Application(('pxe', 'gwh28dgcmp'), 'win10', arch, bootMode, createViewer)
    app.init()
    app.run()

if __name__ == "__main__":
    main(sys.argv)