# Laucher de instalação para windows via redes


### Para Windows 7
É necessário compilar o código para release em x86 e então utilizar os arquivos compactados em "BootFiles/winPE_x86_win7.zip" com o Windows Automated Installation Kit para windows 7.



 - Mountar a imagem do sistem:
```
Dism /Mount-Wim /WimFile:C:\winpe_x86\ISO\sources\boot.wim /index:1 /MountDir:C:\winpe_x86\mount

```

 - Salvar alterações da imagem do sistema:

```
Dism /unmount-Wim /MountDir:C:\winpe_x86\mount /Commit

```

 - Compilar arquivo ISO:
```
oscdimg -n -bC:\winpe_x86\etfsboot.com C:\winpe_x86\ISO C:\winpe_x86\winpe_x86.iso
```

 - Outras informações, acessar os guias presente na documentação o WAIK:
    * Walkthrough: Create a Custom Windows PE Image.
    * Walkthrough: Create a Bootable Windows PE RAM Disk on CD-ROM.
