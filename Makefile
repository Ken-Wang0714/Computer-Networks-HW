all:
	@gcc send_mail.c -o send_mail -g
	@echo "create send_mail"
clean:
	@rm -rf send_mail
	@echo "rm send_mail"