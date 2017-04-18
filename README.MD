# Laucher de instalação para windows via redes


### Para Windows 7
É necessário compilar o código para release em x86 e então utilizar os arquivos compactados em "BootFiles/winPE_x86_win7.zip" com o Windows Automated Installation Kit para windows 7.



 - Mountar a imagem do sistem:
```
Dism /Mount-Wim /WimFile:ISO\sources\boot.wim /index:1 /MountDir:mount

```

 - Salvar alterações da imagem do sistema:

```
Dism /unmount-Wim /MountDir:mount /Commit

```

 - Compilar arquivo ISO:
```
oscdimg -n -betfsboot.com ISO winpe_x86.iso
```

 - Outras informações, acessar os guias presente na documentação o WAIK:
    * Walkthrough: Create a Custom Windows PE Image.
    * Walkthrough: Create a Bootable Windows PE RAM Disk on CD-ROM.


### Para Windows 10 (1607)
É necessário compilar o código para release em x64 e então utilizar os arquivos compactados em "BootFiles/winPE_x64_wi10_1607.zip" com Ambiente de Ferramentas de Implantação e Geração de Imagens o Windows Kits para windows 10.



 - Mountar a imagem do sistem:
```
Dism /Mount-Wim /WimFile:media\sources\boot.wim /index:1 /MountDir:mount

```

 - Salvar alterações da imagem do sistema:

```
Dism /unmount-Wim /MountDir:mount /Commit

```

 - Compilar arquivo ISO para MBR:
```
oscdimg -n -bfwfiles\etfsboot.com media winpe10-1607_x64.iso
```

 - Compilar arquivo ISO para UEFI:
```
oscdimg.exe -bfwfiles\efisys.bin -u2 -udfver102 media winpe10-1604_x64_uefi.iso
```

 - Para forçar o desmontamento da imagem .WIN
```
Imagex /unmount mount
```