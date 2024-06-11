package main

import "database/sql"

func (d *Response) Test(db *sql.DB, data string) {
	d.Msg = "has this interface"
	d.Success = true
}
