import urllib.request, sys, re, string

def downImage(count):
	for i in range(1,count,1):
		fp = urllib.request.urlopen("http://hub.hust.edu.cn/randomImage.action");
		op = open("res/hub_image_" + str(i) + ".jpeg", "wb");
		while 1:
			s = fp.read();
			if not s:
				break;
			op.write(s);
		fp.close();
		op.close();
	return 1;





def main():
	downImage(300);

if __name__ == "__main__":
	main()
