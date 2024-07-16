package br.ufsm;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import org.junit.platform.suite.api.IncludeTags;
import org.junit.platform.suite.api.SelectPackages;
import org.junit.platform.suite.api.Suite;

@Suite
@SelectPackages("br.ufsm")
@IncludeTags("production")
//@IncludeTags({"production","development"}) 

public class ProductionTest
{
}
