# http-copy
This is tool for copy http request to other http server, base on log

# feature
## use simple and safe for master 
## support nginx and support other http server by config

# how to use
## git clone https://github.com/hongliuliao/http-copy
## cd http-copy && make
## cd output && config conf/copy.conf
## nohup ./bin/http_copy &
## curl http://master_server/hello
## see slave server logs

# how to config
## log_reg=.* "GET (.*) HTTP.* ==> log_reg for nginx, the reg in () is url
## log_path=/home/liao/programs/nginx/logs/access.log ==> the log_path to watch
## dist_host=localhost:8081 ==> slave server
