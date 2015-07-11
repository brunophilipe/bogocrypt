## bogocrypt

The stupid encryption+obfuscation algorithm.

### What the fuck is this shit?

This is a thing that came up to my mind one day. It was very simple and easy to implement, and I decided to write it, just for fun.

bogocrypt is a very silly algrithm, and it works in a very silly way. No complex maths involved. But lots of garbage.

### And how does this nonsense work?

bogocrypt needs two things: an input blob and a key.

Assume that:

* `blob` is the input blob. It is an array of bytes.
* `key` is the key. It is also an array of bytes.
* `n` is the length of the key.
* `cypher` is the output blob.

Now, for every `b` bytes from `blob`, `n` bytes will be appended to `cypher`. `n-1` of those bytes can be anything, really. I call them garbage bytes. Only one of those bytes actually has usefull content. I call it needle byte, which is XORed to the respective byte in `key` when written to `cypher` (wrapping around if `n` is greater than the length of `blob`).

Now here comes the tricky part. In order to make this whole mess useful (to some extent), the position of the needle byte needs to be different for every `n` garbage bytes. This creates a challenge for anyone that tries to retrieve information from `cypher`, as they will have a whole lot more garbage than usefull data. And since they don't (well, shouldn't) know the key, they can't technically guess which bytes are garbage and which ones are not.

### "Please don't write your own encryption algorithms!!!111ONE!!"

I know. I don't expect this to be anything but a joke, really. That's why I called it bogocrypt, which was inspired by [bogosort](https://en.wikipedia.org/wiki/Bogosort). I have not put this into any kind of theoretical analysis, and I don't intend to. If you take this thing seriously, you are probably not spending your time wisely (as.. well... me, in fact).

### Usage

So you are *really* interested in seeing how this thing works, eeh? Well, good for you I have prepared a small demo.

Compile simply by running `make`. It has no `make install` rule. Stop being silly. Also, this was written in pure ANSI C and doesn't have any dependencies, so it should work anywhere.

Then use it:

```
$ bogocrypt -e "test" -k 1234
> 4546542307665F516B7D407B0C28475B
$ bogocrypt -d 4546542307665F516B7D407B0C28475B -k 1234
> test
```

It also has an interactive mode :D (now you're thinking "damn, this guy has put a lot of effort in this crappy shit" — yes I did).

Encrypt:

```
$ bogocrypt -i
> bogocrypt - The stupid encryption+obfuscation algorithm.
> Interactive mode: [e:encrypt|d:decrypt]: e
> Insert input (new line marks end - prefered format is base64): YmFuYW5hcyE=
> Insert key (new line marks end - prefered format is byte string): K()"t83d    
> 2110127B714C42794C7C0454191F4C246B183E646107614347535C574B5E1610680E074A2D7C304D1C57531B3B3D7D4F5B722B170C0D7B0450405C2057745F062810612B5F1B73663233032E6E5F682D7D6D45093F6E79484E14561349135F1D
```

Then decrypt:

```
$ bogocrypt -i
> bogocrypt - The stupid encryption+obfuscation algorithm.
> Interactive mode: [e:encrypt|d:decrypt]: d
> Insert input (new line marks end - format is HEX): 2110127B714C42794C7C0454191F4C246B183E646107614347535C574B5E1610680E074A2D7C304D1C57531B3B3D7D4F5B722B170C0D7B0450405C2057745F062810612B5F1B73663233032E6E5F682D7D6D45093F6E79484E14561349135F1D
> Insert key (new line marks end - prefered format is byte string): K()"t83d
> YmFuYW5hcyE=
```

### Future work

Now you just said "reeeally??"

Yes. There are still things that bother me about this algorithm. One of them is that once the key wraps around the input blob, the positions calculated for each needle will also repeat. This could theoretically be used for pattern matching. All my attempts to solve this did not work.