# Laucher de instalação para windows via redes

## Windows 10
É necessário ter instalado o **interpretador Python** referente a arquitetura utilizada, além do Ambiente de Ferramentas de Implantação e Geração de Imagens do **Windows Kits** para Windows 10.

#### Gerando imagem de boot

1. Baixe o instalador executável (``.MSI``) do interpretador Python da arquitetura desejada (``x86-64`` para **64 bits** ou ``x86`` para **32 bits**) na [página de downlods do Python](https://www.python.org/downloads/).
2. Instale o interpretador Python com os seguintes parâmetros:
    * pip;
    * tcl/tk and IDLE;
    * Precompile standard library
    * Apenas pra seu usuário;
3. Instale a biblioteca Resquests:
    ```
    pip install requests
    ```
4. Monte a imagem ``.WIM`` e copie o diretório inteiro da instalação do Python para a raiz da imagem;
5. Extraia os arquivos fonte de ``Dist\NetInstaller 2.0.0.zip`` para a raiz da imagem montada;
6. Modifique o script ``net-installer.bat`` para apontar para o ``python.exe`` correto;
7. Adicione a seguinte linha no final do arquivo ``mount\Windows\System32\startnet.cmd``:
    ```
    %SYSTEMDRIVE%\net-installer.bat
    ```

#### Manipulando a imagem de boot

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
    oscdimg -n -bfwfiles\etfsboot.com media winpe10_x86-64.iso
    ```

 - Compilar arquivo ISO para UEFI:
    ```
    oscdimg.exe -bfwfiles\efisys.bin -u2 -udfver102 media winpe10_x64_uefi.iso
    ```

 - Caso a imagem não consiga desmontar completamente:
    Finalize o processo do Explorer e tente os seguintes comandos:
    ```
    Imagex /unmount mount
    ```
    ou
    ```
    Dism /unmount-Wim /MountDir:mount /Discard
    ```

## Windows 7 (Net Installer v1.0)
Compile o código para release em x86 e então gere uma imagem x86 com o Windows Automated Installation Kit para Windows 7.

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

## Parametros para Debug
 - dboot=<0|1>: Ativa ou desativa a checagem do tipo de boot.