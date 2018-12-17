from Viewer import Viewer
from tkinter import *
from tkinter.ttk import Combobox

def createViewer(dScaling = 0):
    return Viewer({
        'title': 'NetInstaller',
        'resizable': False,
        'widgets': [
            {
                'type': LabelFrame,
                'boder': (1, 'sunken'),
                'fitLayout': False,
                'width': 140,
                'height': 195,
                'text': 'Setup',
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 5, 'pady': 0, 'side': 'left'},
                'widgets': [
                    {
                        'type': Frame,
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3},
                        'widgets': [
                            {
                                'type': Label,
                                'text': 'Endereço do servidor:',
                                'anchor': 'w',
                                'extra': {'fill': 'x'}
                            },
                            {
                                'id': 'serverUrl',
                                'type': Entry,
                                'text': 'server.stein.lan',
                                'extra': {'fill': 'x'}
                            }
                        ]
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 0},
                        'widgets': [
                            {
                                'type': Label,
                                'text': 'Versões disponíveis:',
                                'anchor': 'w',
                                'extra': {'fill': 'x'}
                            },
                            {
                                'type': Frame,
                                'widgets':[
                                    {
                                        'id': 'version-list',
                                        'type': Combobox,
                                        'width': 20,
                                        'readonly': False,
                                        'itens': []
                                    },
                                    {
                                        'id': 'refresh',
                                        'type': Button,
                                        'text': 'Atualizar',
                                        'extra': {'fill': 'x', 'pady': 5}
                                    }
                                ]
                            }
                        ]
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 0},
                        'widgets': [
                            {
                                'type': Label,
                                'text': 'Caminho para instalação:',
                                'anchor': 'w',
                                'extra': {'fill': 'x'}
                            },
                            {
                                'id': 'install-path',
                                'type': Entry,
                                'readonly': True,
                                'text': '',
                                'extra': {'fill': 'x'}
                            }
                        ]
                    },
                    {
                        'type': Frame,
                        'boder': (1, 'sunken'),
                        'fitLayout': False,
                        'extra': {'pady': 5},
                        'width': 140,
                        'height': 2,
                        'widgets':[]
                    },
                    {
                        'type': Label,
                        'text': 'Instalação',
                        'extra': {'fill': 'x', 'padx': 5},
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x'},
                        'widgets': [
                            {
                                'id': 'letter-list',
                                'type': Combobox,
                                'readonly': False,
                                'width': 3,
                                'itens': [],
                                'extra': {'side': 'left', 'padx': 3}
                            },
                            {
                                'id': 'run',
                                'type': Button,
                                'text': 'Iniciar',
                                'width': 30,
                                'font': ("TkDefaultFont", "12", "bold"),
                                'extra': {'side': 'right', "pady": 3, "padx": 3}
                            }
                        ]
                    }
                ]
            },
            {
                'type': LabelFrame,
                'boder': (1, 'sunken'),
                'fitLayout': False,
                'width': 140,
                'height': 63,
                'text': 'Status',
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 5, 'pady': 5},
                'widgets': [
                    {
                        'type': Frame,
                        'extra': {'fill': 'x'},
                        'widgets':[
                            {
                                'type': Label,
                                'text': 'Rede:',
                                'anchor': 'w',
                                'extra': {'side': 'left'}
                            },
                            {
                                'id': 'network-status',
                                'type': Label,
                                'text': 'Não conectado',
                                'font': ("Verdana", "8", "bold"),
                                'anchor': 'w',
                                'extra': {'side': 'left'}
                            }
                        ]
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x'},
                        'widgets':[
                            {
                                'type': Label,
                                'text': 'Modo de boot:',
                                'anchor': 'w',
                                'extra': {'side': 'left'}
                            },
                            {
                                'id': 'boot-mode',
                                'type': Label,
                                'text': 'Desconhecido',
                                'font': ("Verdana", "8", "bold"),
                                'anchor': 'w',
                                'extra': {'side': 'left'}
                            }
                        ]
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x'},
                        'widgets':[
                            {
                                'type': Label,
                                'text': 'Arquitetura:',
                                'anchor': 'w',
                                'extra': {'side': 'left'}
                            },
                            {
                                'id': 'arch',
                                'type': Label,
                                'text': 'Desconhecido',
                                'font': ("Verdana", "8", "bold"),
                                'anchor': 'w',
                                'extra': {'side': 'left'}
                            }
                        ]
                    }
                ]
            },
            {
                'type': LabelFrame,
                'boder': (1, 'sunken'),
                'fitLayout': False,
                'width': 140,
                'height': 90,
                'text': 'Utilitários',
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 5, 'pady': 5},
                'widgets': [
                    {
                        'id': 'load-driver',
                        'type': Button,
                        'text': 'Carregar Driver',
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3}
                    },
                    {   
                        'id': 'run-diskpart',
                        'type': Button,
                        'text': 'Diskpart',
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3}
                    },
                    {
                        'id': 'run-cmd',
                        'type': Button,
                        'text': 'Prompt de Comando',
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3}
                    }
                ]
            },
            {
                'type': Frame,
                'fitLayout': False,
                'width': 140,
                'height': 20,
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 5, 'pady': 10},
                'widgets': [
                    {
                        'type': Label,
                        'text': 'Edwino Stein - 2018 - v2.1.0d',
                        'anchor': 'center'
                    }
                ]
            }
        ]
    }, dScaling)