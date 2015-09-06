/*
** ARexx script for ReTear2.03
** by dBnY^nBS
** takes all packets in given dir and retears them!
*/

/*
** set these to match your systems configuration
*/

Outbound = 'Work:Mail/Outbound/'    /* outbound directory       */
EXE      = 'Work:Mail/ReTear'       /* full path to ReTear      */
Config   = 'Work:Mail/ReTear.cfg'   /* full path to ReTear.cfg  */
Delete   = 1                        /* delete backups?          */

/*
** End of config section
**
** Unless you know what you are doing
** change NOTHING below this point
**/

if right(Outbound,1)~=':' then
    if right(Outbound,1)~='/' then
        Outbound=Insert(Outbound,'/')

IF ~Show('L','rexxsupport.library') then do
    if ~addlib('rexxsupport.library',0,-30,0) then do
        say 'Error Opening Rexxsupport'
        exit 10
    end
end

Dir=ShowDir(Outbound,'F')

Do I=1 to Words(Dir)
    File=Upper(Word(Dir,I))
    BakupNum=0
    OrigFile=Outbound''File
    BakUpFile=Outbound''File'.'BakUpNum
    Do While Exists(BakUpFile)
        BakUpNum=BakUpNum+1
        BakUpFile=Outbound''File'.'BakUpNum
    End

    If (Right(File,4)='.OUT')|(Right(File,4)='.PKT') then do
        Address Command 'Copy 'OrigFile' 'BakUpFile
        Address Command EXE' 'Config' 'BakUpFile' 'OrigFile
        If RC=0 then do
            If Delete=1 then
                Delete(BakUpFile)
        End
        Else do
            Say 'Error ReTearing File'
        End
    End
End


