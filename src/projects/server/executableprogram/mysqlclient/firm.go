package main

type Firm struct {
	ID                 int    `json:"id" gorm:"PRIMARY_KEY;AUTO_INCREMENT"`
	FirmName           string `json:"firmName" gorm:"size:50;NOT NULL"`
	SocialCreditCode   string `json:"socialCreditCode" gorm:"size:18;NOT NULL;UNIQUE"`
	IdentificationCode string `json:"identificationCode" gorm:"size:8;NOT NULL;UNIQUE"`
	InvitationCode     string `json:"invitationCode" gorm:"size:6;NOT NULL"`
	Email              string `json:"email" gorm:"size:50;NOT NULL"`
	CheckNumber        string `json:"checkNumber" gorm:"size:6"`
}
