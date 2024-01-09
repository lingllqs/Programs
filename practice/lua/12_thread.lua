local cr = coroutine.create(function()
	print("Hello Lua")
	local r1, r2, r3 = coroutine.yield(1, 2, 3)
	print(r1, r2, r3)
end)

print(type(cr)) -- thread
coroutine.resume(cr)
coroutine.resume(cr, "a", "b", "c")
