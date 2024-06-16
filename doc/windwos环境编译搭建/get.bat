set temp_dir=E:\Github_Project\build\blueheart\output\temp
set output_dir=E:\Github_Project\build\blueheart\output\bin\Debug
set executableprogram_src_dir=E:\Github_Project\blueheart\src\projects\server\executableprogram

rmdir %temp_dir%
mkdir %temp_dir%

xcopy %executableprogram_src_dir% %temp_dir% /s /v /e

cd %temp_dir%\ziper
go mod init ziper
go mod tidy
go build -o %output_dir%\ziper.exe

rmdir %temp_dir%