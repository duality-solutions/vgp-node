{
	"targets": [
		{
			"target_name": "vgp",
			"sources": [
				"vgp/src/aes256.c",
				"vgp/src/aes256ctr.c",
 				"vgp/src/aes256gcm.c",
 				"vgp/src/curve25519.c",
				"vgp/src/ed25519.c",
				"vgp/src/encryption.cpp",
				"vgp/src/encryption_core.c",
				"vgp/src/encryption_error.c",
 				"vgp/src/fe.c",
 				"vgp/src/ge.c",
				"vgp/src/os_rand.c",
				"vgp/src/rand.c",
				"vgp/src/sha512.c",
				"vgp/src/shake256.c",
				"vgp/src/shake256_rand.c",
				"vgp/src/utils.c",
				"src/hex.cc",
				"src/vgp.cc"
			],
			"include_dirs": [
				"vgp/include",
				"include",
				"<!(node -e \"require('nan')\")"
			],
			"cflags_cc": [
				"-std=c++11"
			],
		}
	]
}
