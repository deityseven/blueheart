mkdir /root/build
cd /root/build
cmake ../shard/blueheart
make -j8
rm -rf /root/build/application
mkdir /root/build/application
cp /root/build/output/bin/checknumberserver /root/build/application
cd /root/build/application
linuxdeployqt checknumberserver -appimage
rm -rf /root/shard/blueheart/application
cp -rf /root/build/application /root/shard/blueheart/
mkdir /root/shard/blueheart/application/config
cp -rf /root/shard/blueheart/doc/config/server_need_change_name_to_network.json /root/shard/blueheart/application/config
mv /root/shard/blueheart/application/config/server_need_change_name_to_network.json /root/shard/blueheart/application/config/network.json

cd /root/shard/blueheart/src/projects/server/checknumberserver/emailsender
go mod init emailsender
go mod tidy
go build -o emailsender

cp -rf ./emailsender /root/shard/blueheart/application

cd /root/shard/blueheart/src/projects/server/checknumberserver/mysqlclient
go mod init mysqlclient
go mod tidy
go build -o mysqlclient

cp -rf ./mysqlclient /root/shard/blueheart/application