attrib -r -a -s -h * /s /d

del /f /s *.ncb *.sbr *.plg *.positions *.ilk *.aps *.suo *.pdb *.asm *.user


chdir SourceCode
rmdir /s /q debug
rmdir /s /q release

