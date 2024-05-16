# algebra
硬件技术团队编程基础作业
## 预修要求｜Requirements
修读过《C程序设计基础》、《线性代数》以及X·Lab硬件技术团队第一次内训或其对应的高阶课程。
## 说明｜Explainations
本题目的难度对于初学者而言相对较高，主要考察了基础的数学能力、通过编程解决问题的能力以及工程管理、CMake、git等综合能力。该作业的最终得分仅作参考，同学们可根据自己的能力来决定实现哪些函数。
## 题目背景｜Background
《线性代数》作为浙江大学工科多数专业必修的数学基础课程，对于其掌握是至关重要的，后续各大专业的专业课程也都离不开线性代数。然而，在后续的专业课程学习中，我们往往只需要计算一些矩阵的数值解，这个过程如果用手去计算的话是十分痛苦的。秉承着“我都学编程了就不要自己做一些无意义的事情”的原则，我们决定实现一个线性代数计算库，来辅助我们进行运算。
> 当然，如MATLAB、Python等高级编程语言已经可以做到这类事情，且做得更好，但这并不妨碍我们通过这样一种方式来锻炼自己的C语言编程能力。
## 题目介绍｜Introduction
本仓库给出了我们在内训中提到的工程模板，同学们要做的任务如下：
1. 自学git，注册GitHub账号，将本仓库在自己的GitHub账户下Fork一份（注意是Fork，禁止直接clone本仓库到本地，否则你将无法完成后续提交），并按照`yourname_hw1`的格式更改仓库名称（在仓库中的Settings处可修改，记得不要用中文，仓库权限为public，如涉及到隐私保护，可设为private，但要将`tanninrachel@yinlin.wiki`这个账户设置为协作者）。
2. 将你的仓库clone到本地。
3. 按照内训所讲的工程模板补充所缺的文件夹。
4. 根据`inc/algebra.h`中的注释和预定义，在`src/algebra.c`中实现对应的函数。
5. 根据内训所讲，自行编写`CMakeLists.txt`文件，使你的工程能够在本地成功编译运行。
6. 自学Markdown，修改`README.md`文件，需要包含你的实现思路（大致描述即可）以及本地运行截图。
7. 将你的修改提交到远程仓库，并将仓库链接提交（提交方式待定）。
## 基本思路｜Thinking
在求矩阵的行列式时，我们在det_matrix函数中，对于1x1的矩阵，直接返回该元素本身；对于2x2的矩阵，返回对角相乘后的减法；对于大于二的对于更大的矩阵，它使用了递归的方法。它通过遍历矩阵的第一行，计算每个元素与其对应的代数余子式的乘积，然后递归调用 `det_matrix` 函数来计算这些代数余子式的行列式，最后将它们加起来作为结果返回。我们构建了`create_submatrix`函数用于创建矩阵的子矩阵。给定一个矩阵 `a` 和一个指定的行列索引 `(row, col)`，它会生成一个新的子矩阵，该子矩阵是通过去除 `a` 中指定行和列的元素而得到的。这个函数在 `det_matrix` 和 `adjugate_matrix` 函数中被调用，用于计算代数余子式。`adjugate_matrix(Matrix a)`: 这个函数用于计算矩阵的伴随矩阵。伴随矩阵是原矩阵的代数余子式的转置矩阵。它通过遍历原矩阵的每个元素，计算其代数余子式的行列式并乘以 (-1)^(i+j)，其中 (i, j) 是元素在原矩阵中的索引。然后，它对这些值进行转置，得到最终的伴随矩阵。进一步，使用transpose_matrix(Matrix a)`交换原矩阵的行和列来得到新的矩阵。

![](D:\xlab\programming basics homework\algebra-initial\README.assets\PixPin_2024-05-16_17-03-58.png)

在求解矩阵的逆时，`inv_matrix()` 函数是计算矩阵逆的主要函数。它首先检查矩阵是否为方阵，然后计算行列式，接着检查行列式是否为零，最后计算伴随矩阵并乘以行列式的倒数来得到逆矩阵。`adjugate_matrix()` 函数用于计算矩阵的伴随矩阵。它遍历原矩阵的每个元素，计算每个元素对应的代数余子式，然后将其放入新矩阵中，并进行适当的符号处理。

![](D:\xlab\programming basics homework\algebra-initial\README.assets\PixPin_2024-05-16_16-55-04.png)

在求解矩阵的秩时，我们使用`rank_matrix(Matrix a)`这个函数用于计算矩阵的秩。它首先创建了矩阵的副本 `matrix`，然后使用高斯消元法将其转换为上三角形式。在转换过程中，它会找到当前列的第一个非零元素，然后将其所在行交换到当前行，接着将当前列下方的元素消为0，然后继续处理下一列。在每次成功找到一个非零元素并进行消元后，秩的值就增加1。最后，函数返回计算得到的秩值。`eliminate_below(double **matrix, int pivot_row, int pivot_col, int rows, int cols)`: 这个函数用于将当前列下方的元素消为0。它接受一个指向矩阵的指针 `matrix`，以及当前主元所在的行号 `pivot_row` 和列号 `pivot_col`，以及矩阵的行数 `rows` 和列数 `cols`。首先获取当前主元的值 `pivot_value`，然后遍历当前列下方的每个元素，计算需要减去的系数，然后更新矩阵中的元素，将其消为0。

![](D:\xlab\programming basics homework\algebra-initial\README.assets\PixPin_2024-05-16_17-20-35.png)

## 交互格式｜Format
在本题目中，`main.c`文件已给出，不需要同学们自己实现，也请不要更改这个文件，否则可能出现判题错误。
### 输入格式
本题目采用帧判定的思路进行，每一帧的第一行指令代码，`+`、`-`、`*`、`.`、`t`、`d`、`i`、`r`、`j`分别测试`add_matrix`、`sub_matrix`、`mul_matrix`、`scale_matrix`、`transpose_matrix`、`det_matrix`、`inv_matrix`、`rank_matrix`、`trace_matrix`函数，`q`表示退出。

接下来的一行输入矩阵 $\mathbf{A}$ 的行数 $m$ 和列数 $n$ ，在接下来的 $m$ 行中输入 $n$ 个双精度浮点数，以空格分开。
对于二元运算函数的测试，需要再按照上述过程输入矩阵 $\textbf{B}$ 。

可能的一次运行输入如下：
```
+
2 2
1.1 1.3
2.4 3.7
2 2
3.1 4.3
5.1 7.1
+
2 2
1.1 1.2
2.4 3.5
2 3
1 2 2.1
3 2 3.3
q
```
### 输出格式
在每一帧中，依次根据输入的指令代码运行对应的函数，并给出函数的输出与标准值比对。上述输入的正确输出如下：
```
4.20    5.60    
7.50    10.80
Error: Matrix a and b must have the same rows and cols.
```
## 评分标准｜Standard
* 成功运行：+25分
* `add_matrix`、`sub_matrix`、`mul_matrix`、`scale_matrix`、`transpose_matrix`、`trace_matrix`功能正常每个+5分
* `det_matrix`、`inv_matrix`、`rank_matrix`功能正常每个+15分
> 为了保证题目难度，每个函数具体的评分标准不予公布。
## 提交方式｜Submit
将你完成任务的GitHub仓库链接通过飞书发送给X-Check机器人，机器人会自动进行打分并将分数返回。参考如下视频：

[https://tannin-1316822731.cos.ap-nanjing.myqcloud.com/2024-03-29-827_1711724348.mp4](https://tannin-1316822731.cos.ap-nanjing.myqcloud.com/2024-03-29-827_1711724348.mp4)