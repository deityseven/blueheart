package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"net/smtp"

	"github.com/jordan-wright/email"
)

type Response struct {
	Success bool   `json:"success"`
	Msg     string `json:"msg"`
}

func main() {
	var res Response
	var senderEmail string
	var senderKey string
	var recverEmail string
	var theme string
	var emailContent string
	var emailServerHost string
	var emailServerPort string

	flag.StringVar(&senderEmail, "senderEmail", "", "发送方邮箱")
	flag.StringVar(&senderKey, "senderKey", "", "发送方授权码")
	flag.StringVar(&recverEmail, "recverEmail", "", "接收方邮箱")
	flag.StringVar(&theme, "theme", "", "邮件主题")
	flag.StringVar(&emailContent, "emailContent", "", "邮件内容")
	flag.StringVar(&emailServerHost, "emailServerHost", "", "邮件服务器地址")
	flag.StringVar(&emailServerPort, "emailServerPort", "", "邮件服务器端口")

	flag.Parse()

	em := email.NewEmail()
	// 设置 sender 发送方 的邮箱 ， 此处可以填写自己的邮箱
	em.From = senderEmail

	// 设置 receiver 接收方 的邮箱  此处也可以填写自己的邮箱， 就是自己发邮件给自己
	em.To = []string{recverEmail}

	// 设置主题
	em.Subject = theme

	// 简单设置文件发送的内容，暂时设置成纯文本
	em.Text = []byte(emailContent)

	//设置服务器相关的配置
	var HostAndPort = emailServerHost + ":" + emailServerPort
	err := em.Send(HostAndPort, smtp.PlainAuth("", senderEmail, senderKey, emailServerHost))
	if err != nil {
		res.Msg = fmt.Sprintf("email sender error : info -> HostAndPort:%s, senderEmail:%s,senderKey:%s,emailServerHost:%s,emailContent%s\n", HostAndPort, senderEmail, senderKey, emailServerHost, emailContent)
		res.Success = false
	} else {
		res.Msg = "success"
		res.Success = false
	}

	data, _ := json.Marshal(res)
	fmt.Print(string(data))
}
