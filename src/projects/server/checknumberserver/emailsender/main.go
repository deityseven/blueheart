package main

import (
	"flag"
	"fmt"
	"net/smtp"

	"github.com/jordan-wright/email"
)

func main() {

	var senderEmail = flag.String("senderEmail", "", "发送方邮箱")
	var senderKey = flag.String("senderKey", "", "发送方授权码")
	var recverEmail = flag.String("recverEmail", "", "接收方邮箱")
	var theme = flag.String("theme", "", "邮件主题")
	var emailContent = flag.String("emailContent", "", "邮件内容")
	var emailServerHost = flag.String("emailServerHost", "", "邮件服务器地址")
	var emailServerPort = flag.String("emailServerPort", "", "邮件服务器地址")

	flag.Parse()

	em := email.NewEmail()
	// 设置 sender 发送方 的邮箱 ， 此处可以填写自己的邮箱
	em.From = *senderEmail

	// 设置 receiver 接收方 的邮箱  此处也可以填写自己的邮箱， 就是自己发邮件给自己
	em.To = []string{*recverEmail}

	// 设置主题
	em.Subject = *theme

	// 简单设置文件发送的内容，暂时设置成纯文本
	em.Text = []byte(*emailContent)

	//设置服务器相关的配置
	var HostAndPort = *emailServerHost + ":" + *emailServerPort
	err := em.Send(HostAndPort, smtp.PlainAuth("", *senderEmail, *senderKey, *emailServerHost))
	if err != nil {
		fmt.Print("error")
	} else {
		fmt.Print("success")
	}
}
