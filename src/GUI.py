from Viewer import Viewer
from tkinter import *
from tkinter.ttk import Combobox

def createViewer():
    return Viewer({
        'title': 'NetInstaller',
        'resizable': False,
        'widgets': [
            {
                'type': LabelFrame,
                'boder': (1, 'sunken'),
                'fitLayout': False,
                'width': 250,
                'height': 225,
                'text': 'Setup',
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 10, 'pady': 5},
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
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3},
                        'widgets': [
                            {
                                'type': Label,
                                'text': 'Versões disponiveis:',
                                'anchor': 'w',
                                'extra': {'fill': 'x'}
                            },
                            {
                                'type': Frame,
                                'widgets':[
                                    {
                                        'id': 'version-list',
                                        'type': Combobox,
                                        'width': 27,
                                        'readonly': False,
                                        'itens': [],
                                        'extra': {'side': 'left'},
                                    },
                                    {
                                        'id': 'refresh',
                                        'type': Button,
                                        'text': 'Atualizar',
                                        'width': 50,
                                        'font': ("Verdana", "7"),
                                        'extra': {'padx': 3}
                                    }
                                ]
                            }
                        ]
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3},
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
                        'width': 240,
                        'height': 2,
                        'widgets':[]
                    },
                    {
                        'type': Label,
                        'text': 'Instalação',
                        'font': ("Verdana", "8"),
                        'extra': {'fill': 'x', 'padx': 5},
                    },
                    {
                        'type': Frame,
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 5},
                        'widgets': [
                            {
                                'id': 'letter',
                                'type': Combobox,
                                'width': 3,
                                'height': 50,
                                'itens': ['A:'],
                                'extra': {'side': 'left', 'padx': 3}
                            },
                            {
                                'id': 'run',
                                'type': Button,
                                'text': 'Inicar',
                                'font': ("Verdana", "10", "bold"),
                                'width': 30,
                                'extra': {'side': 'right', 'padx': 3}
                            }
                        ]
                    }
                ]
            },
            {
                'type': LabelFrame,
                'boder': (1, 'sunken'),
                'fitLayout': False,
                'width': 250,
                'height': 85,
                'text': 'Status',
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 10, 'pady': 5},
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
                        'type': Label,
                        'text': 'Modo de boot: UEFI',
                        'anchor': 'w',
                        'extra': {'fill': 'x'}
                    },
                    {
                        'type': Label,
                        'text': 'Arquitetura: x64',
                        'anchor': 'w',
                        'extra': {'fill': 'x'}
                    }
                ]
            },
            {
                'type': LabelFrame,
                'boder': (1, 'sunken'),
                'fitLayout': False,
                'width': 250,
                'height': 115,
                'text': 'Utilitários',
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 10, 'pady': 5},
                'widgets': [
                    {
                        'type': Button,
                        'text': 'Carregar Driver',
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3}
                    },
                    {
                        'type': Button,
                        'text': 'Diskpart',
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3}
                    },
                    {
                        'type': Button,
                        'text': 'Prompt de Comando',
                        'extra': {'fill': 'x', 'padx': 5, 'pady': 3}
                    }
                ]
            },
            {
                'type': Frame,
                'fitLayout': False,
                'width': 250,
                'height': 20,
                'extra': {'ipadx': 1, 'ipady': 1, 'padx': 0, 'pady': 3},
                'widgets': [
                    {
                        'type': Label,
                        'text': 'Edwino Stein - 2018',
                        'width': 29,
                        'anchor': 'w',
                        'extra': {'side': 'left'},
                    },
                    {
                        'type': Label,
                        'text': 'v2.0.0d',
                        'anchor': 'e',
                        'extra': {'side': 'left'},
                    }
                ]
            }
        ]
    })