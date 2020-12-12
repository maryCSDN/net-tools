CONFIG_ORIGIN 	=config					# -> ../config
CONFIG_DIR		=/etc/net-tools			# 用于存放net-tools配置文件的目录
LOG_DIR 		=/var/log/net-tools		# 用于存放net-tools日志文件的目录

# 创建运行时需要的文件目录
_create_need_direct:
	@mkdir -m 755 -p -v $(CONFIG_DIR)
	chmod 777 $(CONFIG_DIR)/*
	@mkdir -m 755 -p -v $(LOG_DIR)


# 入口
_config:_create_need_direct $(CONFIG_DIR)
	@echo "Start configuration"
	cp -f config/*.conf $(CONFIG_DIR)/