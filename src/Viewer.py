from tkinter import *
from tkinter.ttk import Combobox

class Viewer (object):
    
    supportedTypes = ['Label', 'Button', 'Entry', 'Frame', 'LabelFrame', 'Combobox']

    def __init__(self, cfg, debugScaling = 0):

        self.windowRoot = Tk()

        if debugScaling > 0:
            self.windowRoot.tk.call('tk', 'scaling', debugScaling)

        self.scaling = self.windowRoot.tk.call('tk', 'scaling')

        if 'title' in cfg:
            self.windowRoot.title(cfg['title'])

        if 'size' in cfg:
            self.windowRoot.geometry(cfg['size'])
    
        if 'resizable' in cfg:
            if not cfg['resizable']:
                self.windowRoot.resizable(False, False)

        if 'icon' in cfg:
            self.windowRoot.windowRoot.iconbitmap(cfg['icon'])

        self.widgetsById = {}
        self.widgetsPool = []

        for i in cfg['widgets']:
            self.initWidget(self.windowRoot, i);


    def initWidget(self, parent, cfg):

        if  cfg['type'].__name__ not in self.supportedTypes :
            print("Widget \"" + cfg['type'].__name__ +"\" não suportado!")
            exit(1)

        widget = cfg['type'](parent)
        self.renderWidget(widget, cfg)
        
        self.widgetsPool.append((widget, cfg));

        if cfg['type'].__name__ == 'Label':
            self.initLabel(widget, cfg);
    
        if cfg['type'].__name__ == 'Button':
            self.initButton(widget, cfg);

        if cfg['type'].__name__ == 'Entry':
            self.initEntry(widget, cfg);

        if cfg['type'].__name__ == 'Combobox':
            self.initCombobox(widget, cfg);

        if cfg['type'].__name__ == 'Frame' or cfg['type'].__name__ == 'LabelFrame':
           self.initFrame(widget, cfg)
        
        if 'id' not in cfg:
            cfg['id'] = 'widget-'+ str(len(self.widgetsPool))

        self.widgetsById[cfg['id']] = self.widgetsPool[-1]

        if 'extra' in cfg:
            widget.pack(self.parseExtra(cfg['extra']));
        else:
            widget.pack();
        

    def renderWidget(self, widget, cfg):

        if('text' in cfg):
            widget['text'] = cfg['text'];

        if('font' in cfg):
            widget['font'] = cfg['font'];

        if('width' in cfg):
            widget['width'] = self.toScale(cfg['width']);

        if('height' in cfg):
            widget['height'] = self.toScale(cfg['height']);

        if('color' in cfg):
            widget['fg'] = cfg['color'];

        if('background' in cfg):
            widget['bg'] = cfg['background'];
        
        if 'fitLayout' in cfg:
            widget.pack_propagate(cfg['fitLayout'])

    def initLabel(self, label, cfg):
        if 'anchor' in cfg:
            label['anchor'] = cfg['anchor']

    def initButton(self, btn, cfg):
        if 'onClick' in cfg:
            btn.bind('<Button-1>', self.onBtnClick);

    def initEntry(self, entry, cfg):
        if 'text' in cfg:
            entry.insert(0, cfg['text'])

        if 'visible' in cfg:
            if cfg['visible']:
                entry['show'] = '*'

        if 'readonly' in cfg:
            entry['state'] = 'readonly' if cfg['readonly'] else 'normal'

    def initCombobox(self, combobox, cfg):

        if 'itens' in cfg:
            combobox['values'] = cfg['itens']
        
        if 'readonly' in cfg:
            combobox['state'] = 'disabled' if cfg['readonly'] else 'readonly'


    def initFrame(self, frame, cfg):
        
        if 'boder' in cfg:
           if len(cfg['boder']) >= 1:
               frame['borderwidth'] = self.toScale(cfg['boder'][0])

           if len(cfg['boder']) >= 2:
               frame['relief'] = cfg['boder'][1]

        for i in cfg['widgets']:
            self.initWidget(frame, i);

    def onBtnClick(self, event):
        for i in self.widgetsPool:
            if event.widget == i[0]:
                i[1]['onClick'](i[1]['id'], self, event)

    def addCLickListener(self, widgetId, handle):
        
        if widgetId not in self.widgetsById:
            return
        
        btn = self.widgetsById[widgetId][0]
        btn.bind('<Button-1>', self.onBtnClick);
        cfg = self.widgetsById[widgetId][1]['onClick'] = handle


    def getWidgetById(self, id):
        if id in self.widgetsById:
            return self.widgetsById[id][0]
        else:
            return None

    def toScale(self, value):
        return int(self.scaling * value)

    def parseExtra(self, extra):
        applyScale = ("ipadx", "ipady", "padx", "pady")

        for i in extra:
            if i in applyScale:
                extra[i] = self.toScale(extra[i])

        return extra

    def loop(self):
        self.windowRoot.mainloop()