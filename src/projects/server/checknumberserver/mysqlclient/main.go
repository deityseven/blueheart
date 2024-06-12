package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"reflect"

	"gorm.io/driver/mysql"
	"gorm.io/gorm"
)

type Response struct {
	Success bool   `json:"success"`
	Msg     string `json:"msg"`
}

func interfaceHandel(db *gorm.DB, functionName string, data string) {
	var res Response
	typeT := &res
	arg0 := reflect.ValueOf(db)
	arg1 := reflect.ValueOf(data)
	in := []reflect.Value{arg0, arg1}

	defer func() {
		if err := recover(); err != nil {
			res.Msg = "hasn't this interface"
			res.Success = false
			jsonData, _ := json.Marshal(res)
			fmt.Print(string(jsonData))
		}
	}()

	reflect.ValueOf(typeT).MethodByName(functionName).Call(in)

	jsonData, _ := json.Marshal(res)
	fmt.Print(string(jsonData))
}

func main() {

	var userName string
	var password string
	var serverHost string
	var setvarPort string
	var database string
	var functionNeme string
	var jsonData string

	flag.StringVar(&userName, "userName", "", "username")
	flag.StringVar(&password, "password", "", "password")
	flag.StringVar(&serverHost, "serverHost", "", "mysql server host")
	flag.StringVar(&setvarPort, "setvarPort", "", "mysql server port")
	flag.StringVar(&database, "database", "", "mysql database name")
	flag.StringVar(&functionNeme, "functionNeme", "", "db interface")
	flag.StringVar(&jsonData, "jsonData", "", "db interface need's arg --json")

	flag.Parse()

	//root:123456@tcp(localhost:3306)/tizi365?charset=utf8&parseTime=True&loc=Local&timeout=2s&readTimeout=2s&writeTimeout=10s
	dsn := fmt.Sprintf("%s:%s@tcp(%s:%s)/%s?charset=utf8&parseTime=True&loc=Local&timeout=2s&readTimeout=2s&writeTimeout=10s", userName, password, serverHost, setvarPort, database)
	db, err := gorm.Open(mysql.Open(dsn))

	if err != nil {
		var res Response
		res.Msg = "database open error"
		res.Success = false
		jsonData, _ := json.Marshal(res)
		fmt.Print(string(jsonData))
	} else {
		interfaceHandel(db, functionNeme, jsonData)
	}
}
