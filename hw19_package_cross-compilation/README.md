Клонирую репозитории OpenSSH, OpenSSL, Zlib в виде подмодулей:
```
$ git submodule add git@github.com:openssh/openssh-portable.git
Клонирование в «/home/user/Documents/programming_practice/eltex-ibelash-homework/hw19_package_cross-compilation/openssh-portable»...
remote: Enumerating objects: 72326, done.
remote: Counting objects: 100% (200/200), done.
remote: Compressing objects: 100% (97/97), done.
remote: Total 72326 (delta 140), reused 117 (delta 103), pack-reused 72126 (from 3)
Получение объектов: 100% (72326/72326), 33.31 МиБ | 5.34 МиБ/с, готово.
Определение изменений: 100% (55987/55987), готово.

$ git submodule add git@github.com:openssl/openssl.git
Клонирование в «/home/user/Documents/programming_practice/eltex-ibelash-homework/hw19_package_cross-compilation/openssl»...
remote: Enumerating objects: 562009, done.
remote: Counting objects: 100% (628/628), done.
remote: Compressing objects: 100% (300/300), done.
remote: Total 562009 (delta 448), reused 328 (delta 328), pack-reused 561381 (from 2)
Получение объектов: 100% (562009/562009), 334.97 МиБ | 10.90 МиБ/с, готово.
Определение изменений: 100% (416987/416987), готово.

$ git submodule add git@github.com:madler/zlib.git
Клонирование в «/home/user/Documents/programming_practice/eltex-ibelash-homework/hw19_package_cross-compilation/zlib»...
remote: Enumerating objects: 9045, done.
remote: Counting objects: 100% (117/117), done.
remote: Compressing objects: 100% (19/19), done.
remote: Total 9045 (delta 106), reused 98 (delta 98), pack-reused 8928 (from 2)
Получение объектов: 100% (9045/9045), 4.91 МиБ | 6.47 МиБ/с, готово.
Определение изменений: 100% (6459/6459), готово.
```


