# php7-extension-marmot-encrypt

## 概述

php7 加密解密扩展. 在base64基础上对每个字符做偏移.

## 更新记录

### 20170829

修复在`php_base64_decode_ex`返回时没有判断如果为`null`的bug.