t = {
	a = 100,
}

mt = {
	__index = {
		abc = "123",
		def = "456",
	},
}

setmetatable(t, mt)

print(t["abc"])
print(t["def"])
