var chai = require('chai')
var Build = require('../build')
var expect = chai.expect

describe('Build', function() {
  it('#toTrigger', function() {
    expect(new Build().toTrigger()).to.be.true;
  })
})