package main

import (
	"archive/zip"
	"bytes"
	"io"
	"os"
)

type ZipData struct {
	FilePath string `json:"filePath"`
	JsonData string `json:"jsonData"`
}

func (d *Response) Zip(filePath string, data string) {

	buf := new(bytes.Buffer)
	zipWriter := zip.NewWriter(buf)

	zipFile, err := zipWriter.Create(filePath)
	if err != nil {
		d.Msg = "zip create failed"
		d.Success = false
	}

	_, err = io.WriteString(zipFile, data)
	if err != nil {
		d.Msg = "zip write failed"
		d.Success = false
	}

	err = zipWriter.Close()
	if err != nil {
		d.Msg = "zip close failed"
		d.Success = false
	}

	os.WriteFile(filename+".zip", buf.Bytes(), 0644)

	if len(users) >= 1 {
		d.Msg = "The phone number is registered"
		d.Success = false
	} else {
		d.Msg = "The phone number isn't registered"
		d.Success = true
	}
}

func (d *Response) Unzip(filePath string, data string) {

	if result.Error != nil {
		d.Msg = "add user faild"
		d.Success = false
	} else {
		d.Msg = "add user success"
		d.Success = true
	}
}
