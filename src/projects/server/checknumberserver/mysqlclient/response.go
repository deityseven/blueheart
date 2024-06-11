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
	ID          int    `json:"id" gorm:"PRIMARY_KEY;AUTO_INCREMENT"`
	UserName    string `json:"userName" gorm:"size:50;NOT NULL"`
	Password    string `json:"password" gorm:"size:50"`
	Phone       string `json:"phone" gorm:"size:50;NOT NULL"`
	Email       string `json:"email" gorm:"size:50;NOT NULL"`
	CheckNumber string `json:"checkNumber" gorm:"size:6"`
}

// SELECT EXISTS(SELECT 1 FROM your_table WHERE your_column = 'your_value');
func (d *Response) QueryUserNameIsExist(db *gorm.DB, data string) {
	var user User

	db.Set("gorm:table_options", "ENGINE=InnoDB DEFAULT CHARACTER SET utf8").AutoMigrate(&User{})

	json.Unmarshal([]byte(data), &user)

	var users []User
	db.Where("phone = ?", user.Phone).Find(&users)
	db.Create(&user)
	if len(users) >= 1 {
		d.Msg = "The phone number is registered"
		d.Success = false
	} else {
		d.Msg = "The phone number isn't registered"
		d.Success = true
	}
}
