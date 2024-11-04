/**
  * @file    console_config.h
  * @author  LuckkMaker
  * @brief   Console configuration
  * @version 1.0.0
  * @date    15-Oct-2024
  * @attention
  *
  * Copyright (c) 2024 LuckkMaker
  * All rights reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CONSOLE_CONFIG_H
#define CONSOLE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

//  <q> Use Shell Task While Loop
//  <i> 是否使用默认shell任务while循环
//  <i> 使能此宏，则`shellTask()`函数会一直循环读取输入，一般使用操作系统建立shell
//  <i> 任务时使能此宏，关闭此宏的情况下，一般适用于无操作系统，在主循环中调用`shellTask()`
#define SHELL_TASK_WHILE 1

//  <q> Use Command Export
//  <i> 是否使用命令导出方式
//  <i> 使能此宏后，可以使用`SHELL_EXPORT_CMD()`等导出命令
//  <i> 定义shell命令，关闭此宏的情况下，需要使用命令表的方式
#define SHELL_USING_CMD_EXPORT 1

//  <q> Use Companion Object
//  <i> 是否使用shell伴生对象
//  <i> 一些扩展的组件(文件系统支持，日志工具等)需要使用伴生对象
#define SHELL_USING_COMPANION 1

//  <q> Support End Line
//  <i> 支持shell尾行模式
#define SHELL_SUPPORT_END_LINE 1

//  <q> List User
//  <i> 是否在输出命令列表中列出用户
#define SHELL_HELP_LIST_USER 0

//  <q> List Variable
//  <i> 是否在输出命令列表中列出变量
#define SHELL_HELP_LIST_VAR 0

//  <q> List Key
//  <i> 是否在输出命令列表中列出按键
#define SHELL_HELP_LIST_KEY 0

//  <q> Show Permission
//  <i> 是否在输出命令列表中展示命令权限
#define SHELL_HELP_SHOW_PERMISSION 1

//  <q> Use LF as Enter
//  <i> 使用LF作为命令行回车触发
//  <i> 可以和SHELL_ENTER_CR同时开启
#define SHELL_ENTER_LF 1

//  <q> Use CR as Enter
//  <i> 使用CR作为命令行回车触发
//  <i> 可以和SHELL_ENTER_LF同时开启
#define SHELL_ENTER_CR 1

//  <q> Use CRLF as Enter
//  <i> 使用CRLF作为命令行回车触发
//  <i> 不可以和SHELL_ENTER_LF或SHELL_ENTER_CR同时开启
#define SHELL_ENTER_CRLF 0

//  <q> Use Execute Undefined Function
//  <i> 使用执行未导出函数的功能
//  <i> 启用后，可以通过`exec [addr] [args]`直接执行对应地址的函数
//  <i> 如果地址错误，可能会直接引起程序崩溃
#define SHELL_EXEC_UNDEF_FUNC 0

//  <o> Command Parameter Max Number <8=>8 <16=>16
//  <i> shell命令参数最大数量
//  <i> 包含命令名在内，超过16个参数并且使用了参数自动转换的情况下，需要修改源码
#define SHELL_PARAMETER_MAX_NUMBER 8

//  <o> History Command Max Number <5-10>
//  <i> 历史命令记录数量
#define SHELL_HISTORY_MAX_NUMBER 5

//  <o> Double Click Time <0-1000>
//  <i> 双击间隔(ms)
//  <i> 使能宏`SHELL_LONG_HELP`后此宏生效，定义双击tab补全help的时间间隔
#define SHELL_DOUBLE_CLICK_TIME 200

//  <q> Quick Help
//  <i> 快速帮助
//  <i> 作用于双击tab的场景，当使能此宏时，双击tab不会对命令进行help补全，而是直接显示对应命令的帮助信息
#define SHELL_QUICK_HELP 1

//  <q> Keep Return Value
//  <i> 保存命令返回值
//  <i> 开启后会默认定义一个`RETVAL`变量，会保存上一次命令执行的返回值，可以在随后的命令中进行调用
//  <i> 如果命令的`SHELL_CMD_DISABLE_RETURN`标志被设置，则该命令不会更新`RETVAL`
#define SHELL_KEEP_RETURN_VALUE 0

//  <o> Max Number of Shell <5=>5
//  <i> 管理的最大shell数量
#define SHELL_MAX_NUMBER 5

//  <o> Print Buffer Size <0-1024>
//  <i> shell格式化输出的缓冲大小
//  <i> 为0时不使用shell格式化输出
#define SHELL_PRINT_BUFFER 128

//  <o> Scan Buffer Size <0-1024>
//  <i> shell格式化输入的缓冲大小
//  <i> 为0时不使用shell格式化输入
//  <i> shell格式化输入会阻塞shellTask, 仅适用于在有操作系统的情况下使用
#define SHELL_SCAN_BUFFER 0

//  Get Tick Function
//  获取系统时间(ms)
//  定义此宏为获取系统Tick，如`HAL_GetTick()`
//  此宏不定义时无法使用双击tab补全命令help，无法使用shell超时锁定
#define SHELL_GET_TICK() 0

//  <q> Use Shell Lock
//  <i> 使用锁
//  <i> 使用shell锁时，需要对加锁和解锁进行实现
#define SHELL_USING_LOCK 1

//  Shell Malloc
//  shell内存分配
//  shell本身不需要此接口，若使用shell伴生对象，需要进行定义
#define SHELL_MALLOC(size) NULL

//  Shell Free
//  shell内存释放
//  shell本身不需要此接口，若使用shell伴生对象，需要进行定义
#define SHELL_FREE(obj) NULL

//  <q> Show Shell Info
//  <i> 是否显示shell信息
#define SHELL_SHOW_INFO 1

//  <q> Clear Command Line When Login
//  <i> 是否在登录后清除命令行
#define SHELL_CLS_WHEN_LOGIN 1

//  <s> Default User Name
//  <i> shell默认用户
#define SHELL_DEFAULT_USER "omni"

//  <s> Default User Password
//  <i> shell默认用户密码
//  <i> 若默认用户不需要密码，设为""
#define SHELL_DEFAULT_USER_PASSWORD ""

//  <o> Lock Timeout <0-100000>
//  <i> shell自动锁定超时
//  <i> shell当前用户密码有效的时候生效，超时后会自动重新锁定shell
//  <i> 设置为0时关闭自动锁定功能，时间单位为`SHELL_GET_TICK()`单位
//  <i> 使用超时锁定必须保证`SHELL_GET_TICK()`有效
#define SHELL_LOCK_TIMEOUT 60000

//  <q> Use Function Signature
//  <i> 使用函数签名
//  <i> 使能后，可以在声明命令时，指定函数的签名，shell 会根据函数签名进行参数转换，
//  <i> 而不是自动判断参数的类型，如果参数和函数签名不匹配，会停止执行命令
#define SHELL_USING_FUNC_SIGNATURE 1

//  <q> Support Array Parameter
//  <i> 支持数组参数
//  <i> 使能后，可以在命令中使用数组参数，如`cmd [1,2,3]`
//  <i> 需要使能 `SHELL_USING_FUNC_SIGNATURE` 宏，并且配置 `SHELL_MALLOC`, `SHELL_FREE`
#define SHELL_SUPPORT_ARRAY_PARAM 0

//-------- <<< end of configuration section >>> --------------------------------

#ifdef __cplusplus
}
#endif

#endif /* CONSOLE_CONFIG_H */
