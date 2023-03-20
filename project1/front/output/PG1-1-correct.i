L1:	n = 4
L3:	t1 = 0 * 4
	data [ t1 ] = 44
L4:	t2 = 1 * 4
	data [ t2 ] = 3
L5:	t3 = 2 * 4
	data [ t3 ] = 16
L6:	t4 = 3 * 4
	data [ t4 ] = 4
L7:L8:L9:	swapped = false
L11:	i = 0
L13:	t5 = n - 1
	iffalse i < t5 goto L12
L14:	t6 = i * 4
	t7 = data [ t6 ]
	t8 = i + 1
	t9 = t8 * 4
	t10 = data [ t9 ]
	iffalse t7 > t10 goto L15
L16:	swapped = true
L17:	t11 = i * 4
	temp = data [ t11 ]
L18:	t12 = i * 4
	t13 = i + 1
	t14 = t13 * 4
	t15 = data [ t14 ]
	data [ t12 ] = t15
L19:	t16 = i + 1
	t17 = t16 * 4
	data [ t17 ] = temp
L15:	i = i + 1
L20:	goto L13
L12:	if swapped goto L10
L21:	goto L2
L10:	goto L8
L2:
