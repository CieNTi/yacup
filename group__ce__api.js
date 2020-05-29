var group__ce__api =
[
    [ "ce_channel", "structce__channel.html", [
      [ "command_set", "structce__channel.html#acf95ac3a916f66950cefb082be8e1d60", null ],
      [ "codec", "structce__channel.html#a46a2db4bd09c03f440b4c79a761f5a07", null ],
      [ "data", "structce__channel.html#a2e03252ccb2371ca6f458ba51c4238e9", null ],
      [ "message", "structce__channel.html#a57e26d5e2c9099eb3b15e04283dd5f21", null ]
    ] ],
    [ "ce_codec_encoder", "structce__codec__encoder.html", [
      [ "data", "structce__codec__encoder.html#a94597816b8db6b2679594fd01437a784", null ],
      [ "command", "structce__codec__encoder.html#a5a5917ea4604877af8abdc95ac1723ed", null ],
      [ "message", "structce__codec__encoder.html#a9824424e009cc6350236bb8fa5018f2d", null ]
    ] ],
    [ "ce_codec_decoder", "structce__codec__decoder.html", [
      [ "data", "structce__codec__decoder.html#a00caa22bc155263c8595f40bd120edc3", null ],
      [ "command", "structce__codec__decoder.html#a68f209264f2d71069fac9724bbf8e5b4", null ],
      [ "message", "structce__codec__decoder.html#ac436df74701a5f5ca56ff9af4ffbd585", null ]
    ] ],
    [ "ce_codec", "structce__codec.html", [
      [ "name", "structce__codec.html#adf13f437ac197dcb129e650b889f4477", null ],
      [ "codec_sizeof", "structce__codec.html#ac5f6ca73458b46b307e801a12427e866", null ],
      [ "encode", "structce__codec.html#ab4296a83ca49575728417c43acfacfd1", null ],
      [ "decode", "structce__codec.html#a71c5d8c8ae892846e8fbddcada33a1fe", null ]
    ] ],
    [ "ce_command_argument", "structce__command__argument.html", [
      [ "type", "structce__command__argument.html#afa112cbe3e55adabe83602c400f857cf", null ],
      [ "data", "structce__command__argument.html#a996009e222d65deefea3a7500ecaed73", null ]
    ] ],
    [ "ce_command_listener", "structce__command__listener.html", [
      [ "listener", "structce__command__listener.html#ae6b879943f46f262b654236e3978e5ff", null ],
      [ "argument", "structce__command__listener.html#a44f66a8cc6c8c3f4f0ed4c3d79163334", null ]
    ] ],
    [ "ce_command", "structce__command.html", [
      [ "id", "structce__command.html#af0f9e5d5f16660fb0bde0e81ec045cc2", null ],
      [ "name", "structce__command.html#a82b675b56c34d72bd221cacc7bf7d7d7", null ],
      [ "signature", "structce__command.html#a95c8e2c4fc339c3dbeac10b94ad00f59", null ],
      [ "listener", "structce__command.html#a3d147c285e037c09bc44374b4037bb04", null ]
    ] ],
    [ "ce_command_subset", "structce__command__subset.html", [
      [ "name", "structce__command__subset.html#adfefd855185c9e8f49838000a8143ede", null ],
      [ "command", "structce__command__subset.html#a504f9842a4306eeca2d543f3293d1933", null ]
    ] ],
    [ "ce_command_set", "structce__command__set.html", [
      [ "name", "structce__command__set.html#a0ac7cc6477ea9144daaf131fb5a1122f", null ],
      [ "subset", "structce__command__set.html#ad1341328df5238875046827ce5dd56e7", null ]
    ] ],
    [ "ce_driver", "structce__driver.html", [
      [ "fsm", "structce__driver.html#a3183ee1a6e1c9b0e1d500db60748ceb4", null ],
      [ "send_command", "structce__driver.html#a934ee8d4413cd20a3b8ba79e2a40cb26", null ],
      [ "wait_command", "structce__driver.html#a275459ce62e205f796ba982b8dd59c53", null ]
    ] ],
    [ "ce_data", "unionce__data.html", [
      [ "u8", "unionce__data.html#a5add2eb6cedf3fcd711b147167346a2e", null ],
      [ "i8", "unionce__data.html#a7d0ad4dee1f8be8ea379ad30f144383b", null ],
      [ "u16", "unionce__data.html#a94fb849f59ac20f2250bb867d29f41e9", null ],
      [ "i16", "unionce__data.html#ab889a13082f255d06684f34442d250fe", null ],
      [ "u32", "unionce__data.html#a9c7e462c6a1c5d4dbfe0d35fe6dacf5b", null ],
      [ "i32", "unionce__data.html#a74281f12c5106cc3772cb8c865ffb5a4", null ],
      [ "u64", "unionce__data.html#a166f886e224b6d506328677114a964bc", null ],
      [ "i64", "unionce__data.html#ae22323dd80031879b632527b8a3ccd70", null ],
      [ "f", "unionce__data.html#ab59d9ed20e2c1f4f3b46b25583a643ce", null ],
      [ "d", "unionce__data.html#a98f8c0085690fa624713f48f66cc473f", null ],
      [ "c", "unionce__data.html#a1986738736ebe497e50051698c2cc3e2", null ]
    ] ],
    [ "ce", "structce.html", [
      [ "name", "structce.html#ad1965dfacd6d0856080781fd0ad9d918", null ],
      [ "driver", "structce.html#afccc8a827af75859d0224266d6086094", null ],
      [ "out", "structce.html#ae55d7af9cd06625c10c4c410ef84ccb5", null ],
      [ "in", "structce.html#a42ecc101b267836bee8cf85dfdff26f0", null ]
    ] ],
    [ "ce_data_type", "group__ce__api.html#gafe25fe6ee7696b5a1613ecd64c234be2", null ],
    [ "ce_channel_init", "group__ce__api.html#ga03012ca16c931a830c75d8f43ac6c4bb", null ],
    [ "ce_codec_init", "group__ce__api.html#ga5d72caee899ca86438c14fd306cfcbd7", null ],
    [ "ce_command_locate_by_id", "group__ce__api.html#gaea3edf5686bd9f619d31d901e341da50", null ],
    [ "ce_command_validate", "group__ce__api.html#ga518296b367f5d7d290abf4f333cc918c", null ],
    [ "ce_command_set_listener", "group__ce__api.html#ga5c2e0fc1f08d034c2c408be028e69349", null ],
    [ "ce_init", "group__ce__api.html#gaa038ff9be1d1df5fa24bbfbb4fa69f93", null ],
    [ "ce_tick", "group__ce__api.html#ga19f7b01e42f58a088fd42569f9108dbb", null ],
    [ "ce_send_command", "group__ce__api.html#ga713974077242f97d4e555ff6fe3ac046", null ]
];