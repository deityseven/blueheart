mkdir /root/build
cd /root/build
cmake ../shard/blueheart
make -j8
rm -rf /root/build/application
mkdir /root/build/application
cp /root/build/output/bin/checknumberserver /root/build/application
cp /root/build/output/bin/signinserver /root/build/application
cd /root/build/application
linuxdeployqt checknumberserver -appimage
linuxdeployqt signinserver -appimage
rm -rf /root/shard/blueheart/application
cp -rf /root/build/application /root/shard/blueheart/
mkdir /root/shard/blueheart/application/config
cp -rf /root/shard/blueheart/doc/config/server_need_change_name_to_network.json /root/shard/blueheart/application/config
mv /root/shard/blueheart/application/config/server_need_change_name_to_network.json /root/shard/blueheart/application/config/network.json

rm -rf /root/executableprogram
cp -rf /root/shard/blueheart/src/projects/server/executableprogram /root

cd /root/executableprogram/emailsender
go mod init emailsender
go mod tidy
go build -o /root/shard/blueheart/application/emailsender

cd /root/executableprogram/mysqlclient
go mod init mysqlclient
go mod tidy
go build -o /root/shard/blueheart/application/mysqlclient

cd /root/executableprogram/ziper
go mod init ziper
go mod tidy
go build -o /root/shard/blueheart/application/ziper