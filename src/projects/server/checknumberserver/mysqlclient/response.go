package main

import (
	"encoding/json"

	"gorm.io/gorm"
)

func (d *Response) Test(db *gorm.DB, data string) {
	d.Msg = "has this interface"
	d.Success = true
}

type User struct {
	ID          int    `json:"id"`
	UserName    string `json:"userName"`
	Password    string `json:"password"`
	Phone       string `json:"phone"`
	Email       string `json:"email"`
	CheckNumber string `json:"checkNumber"`
}

// SELECT EXISTS(SELECT 1 FROM your_table WHERE your_column = 'your_value');
func (d *Response) QueryUserNameIsExist(db *gorm.DB, data string) {
	var user User

	db.AutoMigrate(&user)
	json.Unmarshal([]byte(data), &user)

	d.Msg = "has this interface"
	d.Success = true
}
