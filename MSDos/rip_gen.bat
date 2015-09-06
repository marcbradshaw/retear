@echo off
Rem put your packer and unpacker in the path.
Rem put retear and its config files in the dir up from the temp dir and
Rem the outbound dir.
Rem replace <configfile> with your config file. Eg Pc.cfg
Rem replace <outbound> with your outbound dir. Eg outbound
Rem replace <net packet> with your packet file. Eg B869F776.*
Rem replace <temp> with your temp dir. Eg temp.
Rem Replace <unpacker> and <packer> with your compressing program eg Pkunzip
Rem and pkzip
Rem MAKE SURE TEMP exists!

for %%f in (<outbound>\<net packet>.*) do <unpacker> %%f <temp>\ >nul
cd <temp>
for %%f in (*.pkt) do retear <configfile> <temp>\%%f <outbound>\%%f
cd..
for %%f in (<outbound>\<net packet>.*) do <packer> %%f <outbound>\*.pkt 
del <outbound>\*.pkt >nul
del <temp>\*.pkt >nul

