put your packer and unpacker in the path.

put retear and its config files in the dir up from the temp dir and
the outbound dir.
replace <configfile> with your config file. Eg Pc.cfg
replace <outbound> with your outbound dir. Eg outbound
replace <temp> with your temp dir. Eg temp.
MAKE SURE TEMP exists!


If your outbound dir is:  out
 your network packet is:  B869F776
   your temp dir is    :  temp
   your config is      :  wibble.cfg
   your unpacker is    :  pkunzip
   your packer is      :  pkzip

The generic config below... 

for %%f in (<outbound>\<net packet>.*) do <unpacker> %%f <temp>\ >nul
cd <temp>
for %%f in (*.pkt) do retear <configfile> <temp>\%%f <outbound>\%%f
cd..
for %%f in (<outbound>\<net packet>.*) do <packer> %%f <outbound>\*.pkt 
del <outbound>\*.pkt >nul
del <temp>\*.pkt >nul

Is turned into this...

for %%f in (out\B869F776.*) do pkunzip %%f temp\ >nul
cd temp
for %%f in (*.pkt) do retear wibble.cfg temp\%%f out\%%f
cd..
for %%f in (out\B869F776.*) do pkzip %%f out\*.pkt 
del out\*.pkt >nul
del temp\*.pkt >nul


Got it? Good :)

If not... netmail / email Raven at...

2:256/607.20 Fidonet
or
Raven@bleach.demon.co.uk

Hastas my darlings.

/I've lost my purity and pride... All i hide... are terrible lies.../
NiN - Terrible Lies <Empathethic> Halo 3 - (US release) Head Like a Hole
