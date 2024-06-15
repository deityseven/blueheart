package main

import (
	"archive/zip"
	"bytes"
	"encoding/json"
	"io"
	"os"
)

type ZipData struct {
	FilePath string `json:"filePath"`
	JsonData string `json:"jsonData"`
}

func (d *Response) Zip(input string) {

	var zipData ZipData
	json.Unmarshal([]byte(input), &zipData)

	buf := new(bytes.Buffer)
	zipWriter := zip.NewWriter(buf)

	zipFile, err := zipWriter.Create(zipData.FilePath)
	if err != nil {
		d.Msg = "zip create failed"
		d.Success = false
	}

	_, err = io.WriteString(zipFile, zipData.JsonData)
	if err != nil {
		d.Msg = "zip write failed"
		d.Success = false
	}

	err = zipWriter.Close()
	if err != nil {
		d.Msg = "zip close failed"
		d.Success = false
	}

	os.WriteFile(zipData.FilePath, buf.Bytes(), 0644)

	d.Msg = "zip to " + zipData.FilePath
	d.Success = true
}

func (d *Response) Unzip(input string) {
	var zipData ZipData
	json.Unmarshal([]byte(input), &zipData)

	reader, err := zip.OpenReader(zipData.FilePath)
	if err != nil {
		d.Msg = "zip open failed"
		d.Success = false
	}
	defer reader.Close()

	firstFile := reader.Reader.File[0]
	firstFileReader, err := firstFile.Open()
	if err != nil {
		d.Msg = "zip context error"
		d.Success = false
	}
	defer firstFileReader.Close()

	content, err := io.ReadAll(firstFileReader)
	if err != nil {
		d.Msg = "zip file context error"
		d.Success = false
	}

	d.Msg = string(content)
	d.Success = true
}
