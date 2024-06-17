package main

import (
	"archive/zip"
	"bytes"
	"encoding/base64"
	"encoding/json"
	"io"
	"os"
	"time"
)

type ZipData struct {
	FilePath string `json:"filePath"`
	JsonData string `json:"jsonData"`
}

func (d *Response) Zip(input string) {
	time.Sleep(time.Duration(20) * time.Second)

	var zipData ZipData
	json.Unmarshal([]byte(input), &zipData)

	decodedBytes, err := base64.StdEncoding.DecodeString(zipData.JsonData)
	if err != nil {
		d.Msg = "zip DecodeString failed"
		d.Success = false
		return
	}

	zipData.JsonData = string(decodedBytes)

	buf := new(bytes.Buffer)
	zipWriter := zip.NewWriter(buf)

	zipFile, err := zipWriter.Create(zipData.FilePath)
	if err != nil {
		d.Msg = "zip create failed"
		d.Success = false
		return
	}

	_, err = io.WriteString(zipFile, zipData.JsonData)
	if err != nil {
		d.Msg = "zip write failed"
		d.Success = false
		return
	}

	err = zipWriter.Close()

	os.WriteFile(zipData.FilePath, buf.Bytes(), 0644)

	if err != nil {
		d.Msg = "zip close failed"
		d.Success = false
	} else {
		d.Msg = "zip to " + zipData.FilePath
		d.Success = true
	}
}

func (d *Response) Unzip(input string) {
	var zipData ZipData
	json.Unmarshal([]byte(input), &zipData)

	reader, err := zip.OpenReader(zipData.FilePath)
	if err != nil {
		d.Msg = "zip open failed"
		d.Success = false
		return
	}
	defer reader.Close()

	firstFile := reader.Reader.File[0]
	firstFileReader, err := firstFile.Open()
	if err != nil {
		d.Msg = "zip context error"
		d.Success = false
		return
	}
	defer firstFileReader.Close()

	content, err := io.ReadAll(firstFileReader)
	if err != nil {
		d.Msg = "zip file context error"
		d.Success = false
	} else {
		d.Msg = string(content)
		d.Success = true
	}
}
