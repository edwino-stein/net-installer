@ECHO off
wpeutil UpdateBootInfo > null
reg query HKLM\System\CurrentControlSet\Control /v PEFirmwareType
