let chai = require('chai')
let Build = require('../build')
let expect = chai.expect

describe('Build', function() {
  it('#toTrigger', function() {
    expect(new Build().toTrigger())
  })
})