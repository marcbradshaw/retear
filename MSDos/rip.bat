@echo off
Rem put Retear.exe and your packer and unpacker in the path.
for %%f in (outbound\B869F776.*) do pkunzip %%f temp\ >nul
cd temp
for %%f in (*.pkt) do \mailer\retear \mailer\pc.cfg \mailer\temp\%%f \mailer\outbound\%%f
cd..
for %%f in (outbound\B869F776.*) do pkzip %%f outbound\*.pkt 
del \mailer\outbound\*.pkt >nul
del \mailer\temp\*.pkt >nul


