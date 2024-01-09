local M = {}

M.arr = {
	Rust = "good",
	Python = "bad",
}

for k, v in pairs(M.arr) do
	print(k, v)
end

return M
