var ek = ek || {};

function __ekCheckIfObjectExists() {
	return ek._doesObjectExist(this);
}

cc.Node.prototype.exists = __ekCheckIfObjectExists;

cc.Action.prototype.exists = __ekCheckIfObjectExists;

cc.Animation.prototype.exists = __ekCheckIfObjectExists;

cc.SpriteFrame.prototype.exists = __ekCheckIfObjectExists;