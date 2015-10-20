# ITDB-LDAP
本文档描述的是ITDB在使用LDAP用户登录前就将LDAP中某个组的用户加入到ITDB的user表中。
需要实现的功能：
     在ITDB的硬件管理中，需要为硬件指派使用人。
     这个使用人想从LDAP的用户中导入。
流程：
     1、把LDAP中的用导入ITDB的数据库中，就可以了。
但是导入成功后，这些用户也能够登录ITDB了，ITDB默认从LDAP中添加进来的用户的权限是只读。

解决：如何把用户导入到ITDB中？什么时候导入？登录时候导入？还是在为硬件指派使用者时导入？

这里要说明的一点是：ITDB本身也开发了结合LDAP的功能。但是在官方的更新日志上说明了，该LDAP功能是不成熟的，以为着只能满足共享LDAP用户的基本需求。权限控制上也比较单一。要么加入的LDAP用具有只读权限，也可以设置成完全权限。（可以加入后单独设置，也可以在导入前，从配置文件中修改参数，应该是在初始化文件中，init.php）


ITDB本身是如何加入LDAP用户的呢？？？
首先admin/admin登录到ITDB系统。然后在设置中设置好LDAP服务器的相关信息。

现在就可以使用LDAP中的用户和密码登录了。
你第一次设置，肯定是不行的。
可以联通LDAP后，那么就要考虑什么时候将LDAP中的所有用户（或者你选择某个分支）
导入到ITDB中来了。
打开itdb-1.22源代码。
找到init.php的文件
打开。
拉到最下面，找到" ？>“
也就是代码结束的位置。
在问号前一行插入下面代码
////////////////////////////////////////////////////////////////////////////////
    
            $dsn1=ldap_connect("192.168.1.16");//连接到ldap服务器
            $srn1     = ldap_search($dsn1,"ou=People,dc=bawo,dc=cn","(cn=*)");//查询ou=People,dc=bawo,dc=cn下的cn打头的结果，返回到srn1
            $infon1 = ldap_get_entries($dsn1, $srn1); //获得srn1中条目的个数，保存在infon1这个数组中
            for ($i = 1; $i < $infon1["count"]; $i++)//开始循环加入到ITDB的数据库
            //for ($i = 0; $i < 3; $i++)//这个是用来做测试的，只取0,1,2前三个用户加入系统，利于删除
            {
                $usrn1=trim(strtolower($infon1[$i]["cn"][0]));//用户名变成小写，然后打断
                $u=0;
                $u=getuserbyname($usrn1);//getuserbuname用来检查用户名在ITDB数据库中是否存在，如果不存在，返回-1，如果存在则返回$u。
                if ($u==-1){
                  $rnd=mt_rand(); //create a random
                  db_execute2($dbh,
                    "INSERT into users (username,cookie1,usertype) values (:username,:cookie1,:usertype)",
                    array('username'=>$usrn1,'cookie1'=>$rnd,'usertype'=>2));//这个usertype就是创建用户所赋予的权限
                  db_exec($dbh,"UPDATE users set cookie1='$rnd' where username='$usrn1'",1,1);
               } 
          }
////////////////////////////////////////////////////////////
这段代码的意义在于，只要打开ITDB的页面，就会更新LDAP中的ou=People,dc=bawo,dc=cn用户到ITDB的数据库中来。
无论登录的成功与否，都会更新。
