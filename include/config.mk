# -> ../config
CONFIG_ORIGIN 	= config
# 用于存放net-tools配置文件的目录
CONFIG_DIR		= /etc/net-tools
# 用于存放net-tools日志文件的目录
LOG_DIR 		= /var/log/net-tools

# 创建运行时需要的文件目录
_create_need_direct:
	mkdir -p -v $(CONFIG_DIR)
	chmod 777 $(CONFIG_DIR)/*
	mkdir -p -v $(LOG_DIR)
	chmod 777 $(LOG_DIR)


# 入口
_config:_create_need_direct $(CONFIG_DIR)
	cp -f config/*.conf $(CONFIG_DIR)/