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
	Phone       string `json:"phone" gorm:"size:50;NOT NULL;UNIQUE"`
	Email       string `json:"email" gorm:"size:50;NOT NULL"`
	CheckNumber string `json:"checkNumber" gorm:"size:6"`
}

func (d *Response) QueryUserNameIsExist(db *gorm.DB, data string) {
	var user User

	db.Set("gorm:table_options", "ENGINE=InnoDB DEFAULT CHARACTER SET utf8").AutoMigrate(&User{})

	json.Unmarshal([]byte(data), &user)

	var users []User
	db.Where("phone = ?", user.Phone).Find(&users)
	if len(users) >= 1 {
		d.Msg = "The phone number is registered"
		d.Success = false
	} else {
		d.Msg = "The phone number isn't registered"
		d.Success = true
	}
}

func (d *Response) AddUserInfo(db *gorm.DB, data string) {
	var user User

	db.Set("gorm:table_options", "ENGINE=InnoDB DEFAULT CHARACTER SET utf8").AutoMigrate(&User{})

	json.Unmarshal([]byte(data), &user)

	result := db.Create(&user)
	if result.Error != nil {
		d.Msg = "add user faild"
		d.Success = false
	} else {
		d.Msg = "add user success"
		d.Success = true
	}
}

func (d *Response) CheckNumberCompare(db *gorm.DB, data string) {
	var user User

	db.Set("gorm:table_options", "ENGINE=InnoDB DEFAULT CHARACTER SET utf8").AutoMigrate(&User{})

	json.Unmarshal([]byte(data), &user)

	var users []User
	db.Where("phone = ? and check_number = ?", user.Phone, user.CheckNumber).Find(&users)
	if len(users) == 1 {
		d.Msg = "The checkNumber as identical"
		d.Success = true
	} else {
		d.Msg = "The checkNumber as not identical"
		d.Success = false
	}
}

func (d *Response) UpdateUserPassword(db *gorm.DB, data string) {
	var user User

	db.Set("gorm:table_options", "ENGINE=InnoDB DEFAULT CHARACTER SET utf8").AutoMigrate(&User{})

	json.Unmarshal([]byte(data), &user)

	db.Model(&User{}).Where("phone = ?", user.Phone).Update("password", user.Password)

	d.Msg = "update success"
	d.Success = true
}
