import sys, re, string, urllib.request

def downURL (url, filename):
	fp = urllib.request.urlopen(url)
	op = open("./site/" + filename, "wb")
	while 1:
		s = fp.read()
		if not s:
			break;
		op.write(s)
	fp.close()
	op.close()
	return 1

def getURL(url) :
	st = "http://www.qq.com"
	try :
		fp = urllib.request.urlopen(url)
	except :
		return []
	patten = re.compile(r'http://.{0,6}[.].{0,6}[.].{0,6}[.]?.{0,6}/[^\>]+.shtml\b')
	while 1:
		s = fp.read()
		if not s :
			break
		st = st + str(s)
	urls = patten.findall(st)
	fp.close()
	return urls


def spider(startURL, times) :
	urls = []
	urls.append(startURL)
	i = 0
	while 1:
		if i > times :
			break
		if len(urls) > 0:
			url = urls.pop(0)
			#downURL(url, str(i) + '.htm')
			i = i + 1
			if len(urls) < times:
				urllist = getURL(url)
				for url in urllist:
					if urls.count(url) == 0:
						urls.append(url)
						print(url, i)
		else :
			break
	return 1

def main():
	spider("http://sports.sina.com.cn", 2000)

if __name__ == '__main__':
	main()
