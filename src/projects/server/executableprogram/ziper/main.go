package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"reflect"
)

type Response struct {
	Success bool   `json:"success"`
	Msg     string `json:"msg"`
}

func interfaceHandel(functionName string, data string) {
	var res Response
	typeT := &res
	arg0 := reflect.ValueOf(data)
	in := []reflect.Value{arg0}

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

	var functionNeme string
	var jsonData string

	flag.StringVar(&functionNeme, "functionNeme", "", "db interface")
	flag.StringVar(&jsonData, "jsonData", "", "zip interface need's arg --json")

	flag.Parse()

	interfaceHandel(functionNeme, jsonData)
}
